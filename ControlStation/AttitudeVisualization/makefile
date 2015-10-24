all: mavlink_control

mavlink_control: mavlink_control.cpp
	g++ -I/usr/include/python2.7 -I/usr/include/x86_64-linux-gnu/python2.7 -fno-strict-aliasing -D_FORTIFY_SOURCE=2 -g -fstack-protector --param=ssp-buffer-size=4 -Wformat -Werror=format-security  -DNDEBUG -g -fwrapv -O2 -Wall -Wstrict-prototypes -Imavlink/include/mavlink/v1.0 mavlink_control.cpp serial_port.cpp autopilot_interface.cpp ControlStation.cpp -o mavlink_control -lpthread -L/usr/lib/python2.7/config-x86_64-linux-gnu -L/usr/lib -lpthread -ldl  -lutil -lm  -lpython2.7 -Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions

clean:
	 rm -rf *o mavlink_control
