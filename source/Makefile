CXX             = g++ 
SRCS            = $(wildcard *.cpp) $(wildcard *.c)
OBJS            = $(SRCS:.cpp=.o)
TARGET          = compiler2019 
#LIBS            = -lprint
#LIB_DIRS        = -L./lib
#INC             = -I./include
 
all : $(TARGET)
		$(CXX) -o $(TARGET) $(OBJS) #$(INC) $(LIB_DIRS) $(LIBS)
 
$(TARGET) :
		$(CXX) -c $(SRCS) #$(INC) $(LIB_DIRS) $(LIBS)
 
clean :
		rm -f $(TARGET)
		rm -f *.o

