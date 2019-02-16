       #include <unistd.h>
       #include <stdlib.h>
       #include <stdio.h>
       #include<getopt.h>
       #define _GNU_SOURCE

       struct option longopts[] = 
{
	{"initialize", 0, NULL, 'i'},
	{"file", 1, NULL, 'f'},
	{"list", 0, NULL, 'l'},
	{"restart", 0, NULL, 'r'},
	{0, 0, 0, 0}
};
       int
       main(int argc, char *argv[])
       {
           int opt;
           while ((opt = getopt_long(argc, argv, ":if:lr", longopts, NULL)) != -1) {
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
        printf("optind %d\n", optind);
	printf("argc %d\n", argc);
	for (int i = 0; i < argc; i++)
	{
	    printf("argv[%d] = %s\n", i, argv[i]);
	}
        for (; optind < argc; optind++)
	{
	    printf("argument : %s\n", argv[optind]);
	}



           exit(EXIT_SUCCESS);
       }
