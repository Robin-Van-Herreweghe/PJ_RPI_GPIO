src = $(wildcard Program/*.c)
obj = $(src:.c=.o)
CFLAGS=`mysql_config --libs`
Build/main: $(obj)
	$(CC) -o $@ $^ $(CFLAGS)
.PHONY: clean
clean:
	@echo "Lets clean it..."  
	rm -f $(obj) Build/main