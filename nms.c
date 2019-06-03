/*-------------------------------------------------------------------*/
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>

#include "sock.h"
#include "utils.h"
#include "logging.h"

#include "nms.h"
/*-------------------------------------------------------------------*/
#define DBG_PREFIX "OAM-NMS"
#define DEBUG 1
#if DEBUG
#define PRINTD(...) print_dbg(DBG_PREFIX, __VA_ARGS__)
#else /* DEBUG */
#define PRINTD(...) 
#endif /* DEBUG */
/*-------------------------------------------------------------------*/
FILE *nms_log_file;
/*-------------------------------------------------------------------*/
#if 0
static size_t
read_callback(void *dest, size_t size, size_t nmemb, void *userp)
{
  struct WriteThis *wt = (struct WriteThis *)userp;
  size_t buffer_size = size*nmemb;
 
  if(wt->sizeleft) {
    /* copy as much as possible from the source to the destination */ 
    size_t copy_this_much = wt->sizeleft;
    if(copy_this_much > buffer_size)
      copy_this_much = buffer_size;
    memcpy(dest, wt->readptr, copy_this_much);
 
    wt->readptr += copy_this_much;
    wt->sizeleft -= copy_this_much;
    return copy_this_much; /* we copied this many bytes */ 
  }
 
  return 0; /* no more data left to deliver */ 
}
#endif /* 0 */
/*-------------------------------------------------------------------*/
int
proc_nms_input(char *nms_buf, int size)
{
  int i, num_hops;
  struct oam_node *node;
  struct oam_inst *nsi;
  /* char log_str[100]; */
  /* char tmp_str[100]; */
  /* char json_str[200]; */

  printf("[%s] Data from UDP: ", DBG_PREFIX);
  for(i = 0; i < size; i++) {
    printf("%02x:", (uint8_t)nms_buf[i]);
  }
  printf("\b\n");


  /* verify packet type and data */
  if(*((uint8_t *)nms_buf) != 3) {
    return -1;
  }
  num_hops = *((uint8_t *)(nms_buf + 1));
  node = (void *)(nms_buf + 2);
  printf("Packet size: %d\n", size);
  printf("Number of hops: %d\n", num_hops);
  
  /* process NMS input data */
  for(i = 0; i < num_hops; i++) {
    printf("\t* Node: ");
    PRINT_LLADDR(node->lladdr);
    printf("\n\t* Size: %d\n", node->len);

    nsi = (void *)node + CONF_LLADDR_SIZE + 1;
    int j = 0;
    while(j < node->len) {
      /* TODO: process OAM data */
      printf("\t\t+ Type- %d,\tLength- %d,\tVal- ", nsi->type, nsi->len);
      int k;
      for(k = 0; k < nsi->len; k++) {
        printf("%02x:", *((unsigned char *)nsi + 2 + k));
      }
      printf("\n");

      j += 2 + nsi->len;
      nsi = (void *)nsi + j;
    }

    node = (void *)node + CONF_LLADDR_SIZE + 1 + node->len;
    printf("\n\n");
  }


#if 0
  /* read node specific params from 1st entry */
  NTOHS(nms_inst->cpu_temp);
  NTOHS(nms_inst->bat_volt);

  /* copy a blank line to prevent alignment
   * changes made by timestamp printing in log */
  strcpy(log_str, "\n");

  /* Sumit : adding post_date to make life easy for visualization */
  time_t timet;
  time(&timet);
  struct tm* postdate = localtime(&timet);
  char datestr[100];  
  strftime(datestr, sizeof(datestr), "%Y-%m-%d %H:%M:%S", postdate);

  sprintf(tmp_str, "{\"post_date\": \"%s\",", datestr);
  strcpy(json_str, tmp_str);

  strcat(json_str, "\"node\":{\"id\":\"");

  PRINTS_LLADDR(tmp_str, nms_inst->lladdr);
  strcat(log_str, tmp_str);
  strcat(json_str, tmp_str);

  sprintf(tmp_str, " (T: %um degC, BV: %umV)\n",
          nms_inst->cpu_temp, nms_inst->bat_volt);
  strcat(log_str, tmp_str);

  sprintf(tmp_str,
          "\",\"temp\":%u,\"bv\":%u,\"parent\":{\"id\":\"",
          nms_inst->cpu_temp, nms_inst->bat_volt);
  strcat(json_str, tmp_str);

  nms_inst = ((void *) nms_inst) +
         (OAM_INFO_SIZE - LINK_METRICS_SIZE);
  size -= (OAM_INFO_SIZE - LINK_METRICS_SIZE);
  num_els = size/OAM_INFO_SIZE;
  
  /* iterate over the remaining instances */
  for(i = 0; i < num_els; i++) {
    NTOHS((nms_inst + i)->rssi);
    NTOHS((nms_inst + i)->frames_dropped);
    NTOHS((nms_inst + i)->cpu_temp);
    NTOHS((nms_inst + i)->bat_volt);

    /* Prev link specific parameters */
    sprintf(tmp_str, "|\n| (RSSI: %ddB, FD: %u)\n|\n",
            (nms_inst + i)->rssi, (nms_inst + i)->frames_dropped);
    strcat(log_str, tmp_str);

    /* Node specific parameters */
    PRINTS_LLADDR(tmp_str, (nms_inst + i)->lladdr);
    strcat(log_str, tmp_str);
    strcat(json_str, tmp_str);

    sprintf(tmp_str, " (T: %um degC, BV: %umV)\n",
            (nms_inst + i)->cpu_temp, (nms_inst + i)->bat_volt);
    strcat(log_str, tmp_str);

    sprintf(tmp_str,
            "\",\"temp\":%u,\"bv\":%u,\"rssi\":%d,\"fd\":%u,\"parent\":{\"id\":\"",
            (nms_inst + i)->cpu_temp, (nms_inst + i)->bat_volt,
            (nms_inst + i)->rssi, (nms_inst + i)->frames_dropped);
    strcat(json_str, tmp_str);
  }

  strcpy(&json_str[strlen(json_str) - 7], "null");
  for(i = 1; i <= num_els + 2; i++) {
    strcat(json_str, "}");
  }

  /* TODO: Post json_str to server */
  //printf("%s\n", json_str);
  CURL *curl = NULL;
  CURLcode res;
  
  struct WriteThis wt;
  wt.readptr = json_str;
  wt.sizeleft = strlen(json_str);

  curl = curl_easy_init();
  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, TELEMETRY_POST_URL);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
    curl_easy_setopt(curl, CURLOPT_READDATA, &wt);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)wt.sizeleft);

    //need to add Content-Type header in the request
    struct curl_slist *chunk = NULL;
    chunk = curl_slist_append(chunk, "Content-Type:application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

    res = curl_easy_perform(curl);
    /* need to check this, maybe the exponential backoff here as well
       not sure about it, we are logging it locally anyways
    */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    else
      fprintf(stdout, "Successfully posted json to Elasticsearch");
    curl_easy_cleanup(curl);
  }

  /* print current OAM data to log */
  print_log_str(nms_log_file, log_str);
  printf("%s", log_str);
#endif /* 0 */

  return 0;
}
/*-------------------------------------------------------------------*/
int
main(/* int argc, char* argv[]*/)
{
  int nms_sock;
  fd_set read_handles;
  struct sockaddr_in6 remote_addr;
  int remote_addr_len;
  int recv_size;

  char nms_buf[100];
  
  /* setup and listen for connections */
  if((nms_sock = udp_socket_setup()) < 0) {
    exit(EXIT_FAILURE);
  }

  if(bind_host_addr6(nms_sock, in6addr_any, htons(NMS_PORT)) < 0) {
    exit(EXIT_FAILURE);
  }

  PRINTD("Configured with port: %d", NMS_PORT);

  read_handles = assign_read_handle(nms_sock);

  /* init remote_addr params */
  remote_addr.sin6_family = AF_INET6;
  remote_addr_len = 40;

  /* create log for nms */
  nms_log_file = create_log("nms-ioam", 0, 0);

  while(1) {
    /* listen on assigned read_handle */
    if((recv_size = udp_listen(nms_sock, read_handles,
             (struct sockaddr *) &remote_addr,
             (int *) &remote_addr_len, nms_buf,
             sizeof(nms_buf))) <=0 ) {
      sleep(5);
      continue;
    }
    /* PRINTD("Recieved NMS packet: %d bytes", recv_size); */

    proc_nms_input(nms_buf, recv_size);
  }
  return 0;
}
/*-------------------------------------------------------------------*/
