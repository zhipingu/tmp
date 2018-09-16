#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1
#define true 1
#define false 0
#define MaxLine 1005

/* this function isn't universally available, here is a local version,
       returns pointer in txt to first place where pat occurs, and returns
       NULL if pat does not occur in txt, doing case-insensitive tests
*/
const char* mystrcasestr(const char *txt, const char *pat) {
	int tl=strlen(txt);
	int pl=strlen(pat);
	int i;
	for (i=0; i<=tl-pl; i++) {
	    if (strncasecmp(txt+i, pat, pl)==0) {
		return txt+i;
	    }
	}
	return NULL;
}

int read_data(char store[1000][25])
{
    int line_num=0;
    while(gets(store[line_num++])!=NULL);
    --line_num;

#if DEBUG
    printf("=========\n");
    for(int i=0;i<line_num;++i)
        printf("%s\n",store[i]);
#endif    

    return line_num;
}

/* state is the output parameter
 * state==0 overlap length is 0
 * state==1 substr
 * state==2 overlap part
*/
size_t overlap(char* str1, char* str2) {
    size_t len1=strlen(str1);
    size_t len2=strlen(str2);
    size_t max_overlap = 0;
    
    // i must be declared as int because size_t vars can't go <0
    for (int i = len1-1; i >= 0; --i) {
        size_t j = 0;  // current number of overlapping characters
        int overlapping = true;
        while (j < len2 && i+j < len1 && overlapping) {
            if (str1[i+j] != str2[j]) {
                overlapping = false;
            } else {
                ++j;
            }
        }
        // We have 3 cases for the cycle to exit:
        // 1) j == len2 means that str2 is a substring of str1
        // this means that no other best solution can be found
        if (j == len2) {
            return len2;
        }
        // 2) i+j == len1 means a prefix of str2 is a suffix of str1
        // Candidate to be the best local overlap
        if (i+j == len1) {
            max_overlap = j;
        }
        // 3) overlapping == false means that we must go on
    }
    return max_overlap;
}

void max_overlap(char store[1000][25])
{
    char superstring[1000*20];
    int processed[1000]={0};
    int length_overlap[1000]={0};
    strcpy(superstring,store[0]);
    processed[0]=1;

    int max=0;
    int index=-1;
    int cnt_processed=0;
    while(cnt_processed==1000)
    {
        for(int i=1;i<1000;++i)
        {
            if(processed[i]==1)
                continue;
            int overlap_len=overlap(superstring,store[i]);
            if(overlap_len == strlen(store[i]))
            {
                processed[i]=1;
                ++cnt_processed;
            }
            else
            {
                length_overlap[i]=overlap_len;
                if(overlap_len>max)
                {
                    max=overlap_len;
                    index=i;    
                }
            }
        }
        strcat(superstring,store[index]+max);
        processed[index]=1;
        max=0;
        ++cnt_processed;
    }

}
int main()
{
	char* p="abcq";
    char* p1="cqsdkfjdkl";
    char store[1000][25];
//    read_data(store);
    printf("%lu\n",overlap(p,p1));
    //printf("%s\n",mystrcasestr(p1,p));


}
