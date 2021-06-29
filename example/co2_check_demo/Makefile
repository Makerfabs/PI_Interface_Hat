DIR_Config   = ./lib/Config
DIR_EPD      = ./lib/LCD
DIR_FONTS    = ./lib/Fonts
DIR_GUI      = ./lib/GUI
DIR_TOUCH      = ./lib/Touch
DIR_ADC      = ./lib/ADC
DIR_SRC 	 = ./src
DIR_BIN      = ./bin

OBJ_C = $(wildcard ${DIR_EPD}/*.c ${DIR_Config}/*.c ${DIR_GUI}/*.c ${DIR_SRC}/*.c ${DIR_FONTS}/*.c ${DIR_TOUCH}/*.c ${DIR_ADC}/*.c)
OBJ_O = $(patsubst %.c,${DIR_BIN}/%.o,$(notdir ${OBJ_C}))

USELIB = USE_WIRINGPI_LIB
DEBUG = -D $(USELIB)
LIB = -lwiringPi -lm 
TARGET = co2_check


CC = gcc
MSG = -g -O0 -Wall
CFLAGS += $(MSG) $(DEBUG)

${TARGET}:${OBJ_O}
	$(CC) $(CFLAGS) $(OBJ_O) -o $@ $(LIB)
    
${DIR_BIN}/%.o:$(DIR_SRC)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ -I $(DIR_Config) -I $(DIR_GUI) -I $(DIR_EPD)  -I $(DIR_TOUCH) -I $(DIR_ADC)
    
${DIR_BIN}/%.o:$(DIR_EPD)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ -I $(DIR_Config)
    
${DIR_BIN}/%.o:$(DIR_FONTS)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@
    
${DIR_BIN}/%.o:$(DIR_GUI)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ -I $(DIR_Config)  -I $(DIR_EPD) -I $(DIR_SRC)

${DIR_BIN}/%.o:$(DIR_Config)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ $(LIB)

${DIR_BIN}/%.o:$(DIR_TOUCH)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ $(LIB) -I $(DIR_Config)

${DIR_BIN}/%.o:$(DIR_ADC)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ $(LIB) -I $(DIR_Config)
	
clean :
	rm -rf *.wav
	rm $(DIR_BIN)/*.* 
	rm $(TARGET) 

