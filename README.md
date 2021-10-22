Building on the post from kev

From the linux/joystick.h file:

    struct js_event {
    	__u32 time;	    /* event timestamp in milliseconds */
	    __s16 value;	/* value */
    	__u8 type;	    /* event type */
    	__u8 number;	/* axis/button number */
    };

So the [python format][1] should be:"LhBB"

    infile_path = "/dev/input/js0"
    EVENT_SIZE = struct.calcsize("LhBB")
    file = open(infile_path, "rb")
    event = file.read(EVENT_SIZE)
    while event:
        print(struct.unpack("LhBB", event))
        (tv_msec,  value, type, number) = struct.unpack("LhBB", event)
        event = file.read(EVENT_SIZE)

sample output from XBOX One S controller:

    // type=button, number=button number
    //msec, value, type, number
    (2114530, 1, 1, 0) // A pressed
    (2114670, 0, 1, 0) // A released
    (2116490, 1, 1, 1) // B pressed
    (2116620, 0, 1, 1) // B released
    (2117370, 1, 1, 2) // X pressed
    (2117520, 0, 1, 2) // X released
    (2118220, 1, 1, 3) // Y pressed
    (2118360, 0, 1, 3) // Y released

  [1]: https://docs.python.org/2/library/struct.html

################################################################
################################################################

This page: http://scaryreasoner.wordpress.com/2008/02/22/programming-joysticks-with-linux/ has a nice writeup on how to read the info from /dev/input/js0

The format of the events you read from the file are documented here: https://www.kernel.org/doc/Documentation/input/input.txt . It's a simple struct containing a timestamp, the event type and identifier and the value:

    struct input_event {
    	struct timeval time;
    	unsigned short type;
    	unsigned short code;
    	unsigned int value;
    };

