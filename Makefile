PROJ = nms
HOST_DIR = .
OUT_FILE = nms.o

include $(HOST_DIR)/Makefile.include
include $(UTIL_DIR)/Makefile

oam-nms: nms.c $(UTIL_TARGETS)
	$(CC) $(CFLAGS) $(INC) -o $(OUT_FILE) $(UTIL_OBJS) nms.c $(LDFLAGS)

start-nms:
	./$(OUT_FILE)
