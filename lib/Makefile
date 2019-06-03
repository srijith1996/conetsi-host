# Make targets for utility files
# do not run make in this directory
# you can access these targets in the main directory

UTIL_TARGETS = socket-util.o logging.o utils.o
UTIL_OBJS = $(OBJ_DIR)/socket-util.o $(OBJ_DIR)/logging.o $(OBJ_DIR)/utils.o


socket-util.o: $(UTIL_DIR)/socket-util.c obj_dir
	$(CC) $(CFLAGS) $(INC) -c -o $(OBJ_DIR)/socket-util.o $(UTIL_DIR)/socket-util.c

logging.o: $(UTIL_DIR)/logging.c obj_dir utils.o
	$(CC) $(CFLAGS) $(INC) -c -o $(OBJ_DIR)/logging.o $(UTIL_DIR)/logging.c $(LDFLAGS)

utils.o: $(UTIL_DIR)/utils.c obj_dir
	$(CC) $(CFLAGS) $(INC) -c -o $(OBJ_DIR)/utils.o $(UTIL_DIR)/utils.c

