#include <common/stdlib.h>
#include <stdint.h>

// raspi model 1 does not have division instruction, so we need to define our own
__inline__ uint32_t div(uint32_t dividend, uint32_t divisor) {
#ifdef MODEL_1
    // Use long division, but in binary.  Copied from Stack overflow...
    uint32_t denom=divisor;
    uint32_t current = 1;
    uint32_t answer=0;

    if ( denom > dividend)
        return 0;

    if ( denom == dividend)
        return 1;

    while (denom <= dividend) {
        denom <<= 1;
        current <<= 1;
    }

    denom >>= 1;
    current >>= 1;

    while (current!=0) {
        if ( dividend >= denom) {
            dividend -= denom;
            answer |= current;
        }
        current >>= 1;
        denom >>= 1;
    }
    return answer;
#else
    return dividend / divisor;
#endif
}

__inline__ divmod_t divmod(uint32_t dividend, uint32_t divisor) {
    divmod_t res;
#ifdef MODEL_1
    res.div = div(dividend, divisor);
    res.mod = dividend - res.div*divisor;
#else
    res.div = dividend / divisor;
    res.mod = dividend % divisor;
#endif
    return res;
}

void memcpy(void * dest, const void * src, int bytes) {
    char * d = dest;
    const char * s = src;
    while (bytes--) {
        *d++ = *s++;
    }
}

void bzero(void * dest, int bytes) {
    memset(dest, 0, bytes);
}

void memset(void * dest, uint8_t c, int bytes) {
    uint8_t * d = dest;
    while (bytes--) {
        *d++ = c;
    }
}

char * itoa(int num, int base) {
    static char intbuf[33];
    uint32_t j = 0, isneg = 0, i;
    divmod_t divmod_res;

    if (num == 0) {
        intbuf[0] = '0';
        intbuf[1] = '\0';
        return intbuf;
    }

    if (base == 10 && num < 0) {
        isneg = 1;
        num = -num;
    }

    i = (uint32_t) num;

    while (i != 0) {
       divmod_res = divmod(i,base);
       intbuf[j++] = (divmod_res.mod) < 10 ? '0' + (divmod_res.mod) : 'a' + (divmod_res.mod) - 10;
       i = divmod_res.div;
    }

    if (isneg)
        intbuf[j++] = '-';

    if (base == 16) {
        intbuf[j++] = 'x';
        intbuf[j++] = '0';
    } else if(base == 8) {
        intbuf[j++] = '0';
    } else if(base == 2) {
        intbuf[j++] = 'b';
        intbuf[j++] = '0';
    }

    intbuf[j] = '\0';
    j--;
    i = 0;
    while (i < j) {
        isneg = intbuf[i];
        intbuf[i] = intbuf[j];
        intbuf[j] = isneg;
        i++;
        j--;
    }

    return intbuf;
}

int atoi(char * num) {
    int res = 0, power = 0, digit, i;
    char * start = num;

    // Find the end
    while (*num >= '0' && *num <= '9') {
        num++;     
    }

    num--;

    while (num != start) {
        digit = *num - '0'; 
        for (i = 0; i < power; i++) {
            digit *= 10;
        }
        res += digit;
        power++;
        num--;
    }

    return res;
}

int rand(int max)
{
    static long a = 3;
    a = (((a * 214013L + 2531011L) >> 16) & 32767);
        
    return ((a % max) + 1);
}

uint8_t ctohex(int v){
    if(v > 255 || v < 255) return 255;

    return (v && 0xff);
}

uint32_t strlen(const char *str)
{
    int count = 0;
    while(*str!='\0'){
        count++;
        str++;
    }
    return count;
}

void append(char* s, char c) {
        uint32_t len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

int strcomp(char stringa[], char stringb[]) {
    int i;
    // Compare for i=0 to the point where stringa doesnt match stringb anymore
    for(i=0; stringa[i] == stringb[i]; i++){
        // if we have reached the end of stringa and the strings are still equal
        // then we can return 0 because both strings are equal
        if(stringa[i] == '\0') return 0;
    }
    return stringa[i] - stringb[i];
}