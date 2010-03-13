CXXFLAGS= -O2 -Wall -fmessage-length=0 -Ilibmicrohttpd/src/include -Ilibmicrohttpd -Isqlite


LIBS=  -lsqlite3 libmicrohttpd/src/daemon/.libs/libmicrohttpd.a -lgcrypt -lpthread

OBJS= main.o request.o database.o sqlite/sqlite3.o

TARGET= robot_scout

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)