       #include <unistd.h>
       #include <stdlib.h>
       #include <stdio.h>

       int
       main(int argc, char *argv[])
       {
           int opt;
           while ((opt = getopt(argc, argv, ":if:lr")) != -1) {
               switch (opt) {
               case 'i':
               case 'l':
	       case 'r':
	    	   printf("option %c\n", opt);
                   break;
	       case 'f':
		   printf("filename : %s\n", optarg);
		   break;
	       case ':':
                   printf("option needs a value\n");
                   break;
	       case '?':
		   printf("unknow option : %c\n", optopt);
       	           break;
	       default: /* '?' */
                   printf("unknow option %c\n", opt);
		   break;
	       }
           }

        for (; optind < argc; optind++)
	{
	    printf("argument : %s\n", argv[optind]);
	}



           exit(EXIT_SUCCESS);
       }
