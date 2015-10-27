// Check your Scanf and Printf later
// gcc -Wall prog.c -o prog -lcrypto -lssl  -lcurl
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>

#if defined(__APPLE__)
#  define COMMON_DIGEST_FOR_OPENSSL
#  include <CommonCrypto/CommonDigest.h>
#  define SHA1 CC_SHA1
#else
#  include <openssl/md5.h>
#endif
char *str2md5(const char *str, int length) {
    int n;
    MD5_CTX c;
    unsigned char digest[16];
    char *out = (char*)malloc(33);

    MD5_Init(&c);

    while (length > 0) {
        if (length > 512) {
            MD5_Update(&c, str, 512);
        } else {
            MD5_Update(&c, str, length);
        }
        length -= 512;
        str += 512;
    }

    MD5_Final(digest, &c);

    for (n = 0; n < 16; ++n) {
        snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
    }

    return out;
}

    int main(int argc, char **argv) {
//		
		char user_name[100] = "inquisitor@gmail.com"; // Will be provided by SP sames as the nounce
		char postDataPass[100] = "pass=";
		char postDataUser[100] = "&user=";
		char stored_pass[100] = "hello";
		char *entered_pass;
		char google_nounce[100] = "nounce";
		char combined[100] = "";
		//printf("Please enter your username. \n");
		//scanf("%s", user_name);
		printf("Please enter your password code. \n");
		entered_pass = getpass("Password: ");		
			if (strcmp(stored_pass, entered_pass) == 0){
				printf("Success :) \n"); // Print success 
		strcat(combined, stored_pass);
		strcat(combined, google_nounce);
       	 	char *hashCombined = str2md5(combined, strlen(combined)); // Hash the enetered_pass
        	printf("%s\n", hashCombined);
		// CURL Stuff
		CURL *curl;
		  CURLcode res;
		  curl_global_init(CURL_GLOBAL_ALL); // In Windows, init Winsock
		  curl = curl_easy_init(); //get a curl handl
		  if(curl) {
		    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/tee/index.php"); // URL 
		    strcat(postDataPass,hashCombined);
		    strcat(postDataPass,postDataUser);
		    strcat(postDataPass,user_name);
			printf("%s\n", postDataPass);
		    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postDataPass); // Data to be posted
		    res = curl_easy_perform(curl); // perform the request and res will get the return code
 		   if(res != CURLE_OK) // Check for Errors
 		     fprintf(stderr, "curl_easy_perform() failed: %s\n",
 		             curl_easy_strerror(res));
 		   curl_easy_cleanup(curl); // Clean the house :)
		  }
		  curl_global_cleanup();
		        	free(hashCombined);
				}
					else{
					printf("Fail :( \n");
				}
//
        return 0;
    }
