#include <stdio.h>

void
print_usage() {
	fprintf(stderr, "usage: hex2bin input_text_file output_bin_file\n");
}

int
main(int argc, char *argv[]) {
	FILE *infile, *outfile;
	char hexbyte[3];
	int hbi;
	char c;

	if(argc<3) {
		print_usage();
		return -1;
	}
	
	
	infile=fopen(argv[1], "r");
	outfile=fopen(argv[2], "w");

	hbi=0;
	hexbyte[2]=0;
	
	while(fread(&c, 1, 1, infile)) {
		// skip non-nex ascii characters
		if(	(c<48 || c>57)	/* ! 0-9 */ &&
			(c<65 || c>70)	/* ! A-F */ &&
			(c<97 || c>102)	/* ! a-f */	) continue;
		
		hexbyte[hbi]=c;
		hbi^=1;

		if( hbi == 0 ) {
			c=strtol(hexbyte, NULL, 16);
			fwrite(&c, 1, 1, outfile);
		}
	
	}
	
	
	fclose(infile);
	fclose(outfile);

	return 0;
}

