PROG = toggle

run: $(PROG)
	./$(PROG) $(ARGS)

$(PROG): main.c mongoose.c packed_fs.c Makefile
	$(CC) main.c mongoose.c packed_fs.c -W -Wall -DMG_ENABLE_PACKED_FS=1 -Ipc/ $(CFLAGS_EXTRA) -o $@

packed_fs.c: $(wildcard web_root/*)
	node pack.js web_root/* > $@

stm32:

skeletons:
	git clone -q --depth 1 -b v1.0.0 https://github.com/cesanta/skeletons.git $@
