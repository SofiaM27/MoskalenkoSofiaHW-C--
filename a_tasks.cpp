
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define OUT_REPLACED "output_replaced.txt"

static char* read_file(const char* path, size_t* out_len) {
    FILE* f = fopen(path, "rb");
    if (!f) { fprintf(stderr, "Failed to open file: %s\n", path); return NULL; }
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    fseek(f, 0, SEEK_SET);
    char* buf = (char*)malloc((size_t)sz + 1);
    if (!buf) { fclose(f); return NULL; }
    size_t rd = fread(buf, 1, (size_t)sz, f);
    fclose(f);
    buf[rd] = '\0';
    if (out_len) *out_len = rd;
    return buf;
}

static int is_word_byte(unsigned char c) {
    if (isalnum(c)) return 1;
    if (c >= 128) return 1;
    return 0;
}

static int is_date_sep(char c) {
    return c == '.' || c == '/' || c == ':' || c == '-';
}

static const char* month_names[13] = {
    "", "January","February","March","April","May","June",
    "July","August","September","October","Nowember","Decemder"
};

//Task 1
static void task1_links(const char* text) {
    printf("Task 1: links and the word before them\n");
    const char* p = text;
    while (1) {
        const char* h1 = strstr(p, "http://");
        const char* h2 = strstr(p, "https://");
        const char* h = NULL;
        if (h1 && h2) h = (h1 < h2) ? h1 : h2;
        else h = h1 ? h1 : h2;
        if (!h) break;

        const char* q = h;
        while (*q && !isspace((unsigned char)*q)) q++;

        const char* wend = h;
        const char* t = h;
        while (t > text && (isspace((unsigned char)*(t-1)) || ispunct((unsigned char)*(t-1)))) t--;
        const char* wstart = t;
        while (wstart > text && is_word_byte((unsigned char)*(wstart-1))) wstart--;
        if (wstart < t) {
            int wlen = (int)(t - wstart);
            printf("Слово перед: %.*s\n", wlen, wstart);
        } else {
            printf("Слово перед: (немає)\n");
        }
        printf("URL: %.*s\n\n", (int)(q - h), h);

        p = q;
    }
}

//Task 2
static int parse_date_at(const char* s, size_t len, size_t pos, size_t* out_start, size_t* out_end, int* out_d, int* out_m, int* out_y) {
    size_t i = pos;
    while (i < len && isspace((unsigned char)s[i])) i++;
    if (i >= len || !isdigit((unsigned char)s[i])) return 0;
    size_t start = i;
    int a = 0; int a_len = 0;
    while (i < len && isdigit((unsigned char)s[i]) && a_len < 4) { a = a*10 + (s[i]-'0'); i++; a_len++; }
    if (i >= len) return 0;
    if (!is_date_sep(s[i])) return 0;
    char sep1 = s[i++];
    if (i >= len || !isdigit((unsigned char)s[i])) return 0;
    int b = 0; int b_len = 0;
    while (i < len && isdigit((unsigned char)s[i]) && b_len < 2) { b = b*10 + (s[i]-'0'); i++; b_len++; }
    if (i >= len) return 0;
    if (!is_date_sep(s[i])) return 0;
    char sep2 = s[i++];
    if (i >= len || !isdigit((unsigned char)s[i])) return 0;
    int c = 0; int c_len = 0;
    while (i < len && isdigit((unsigned char)s[i]) && c_len < 4) { c = c*10 + (s[i]-'0'); i++; c_len++; }

    int day=0, mon=0, year=0;
    if (a_len == 4) {
        year = a; mon = b; day = c;
    } else if (c_len == 4) {
        day = a; mon = b; year = c;
    } else {
        day = a; mon = b; year = c;
        if (year < 100) year += 2000;
    }

    if (!(mon >= 1 && mon <= 12 && day >= 1 && day <= 31 && year >= 1 && year <= 9999)) return 0;

    *out_start = start;
    *out_end = i;
    *out_d = day; *out_m = mon; *out_y = year;
    return 1;
}

static void task2_find_and_print_dates(const char* text, size_t len) {
    printf("Task 2: find dates and convert to the format (year) month_name (number)\n");
    size_t i = 0;
    int found = 0;
    while (i < len) {
        size_t st=0, ed=0; int d=0,m=0,y=0;
        if (parse_date_at(text, len, i, &st, &ed, &d, &m, &y)) {
            found = 1;
            const char* mname = (m>=1 && m<=12) ? month_names[m] : "??";
            printf("Found: %.*s  ->  (%04d) %s ( %d )\n",
                   (int)(ed-st), text+st, y, mname, d);
            i = ed;
        } else {
            i++;
        }
    }
    if (!found) printf("Date not found.\n");
}

// Task 3
static int parse_number_at(const char* s, size_t len, size_t pos, size_t* out_start, size_t* out_end, double* out_val) {
    size_t i = pos;
    while (i < len && isspace((unsigned char)s[i])) i++;
    size_t start = i;
    int any = 0;
    if (i < len && (s[i] == '+' || s[i] == '-')) { i++; any = 1; }
    int digits_before = 0;
    while (i < len && isdigit((unsigned char)s[i])) { i++; digits_before++; any = 1; }
    if (i < len && (s[i] == '.' || s[i] == ',')) {
        i++;
        int digits_after = 0;
        while (i < len && isdigit((unsigned char)s[i])) { i++; digits_after++; any = 1; }
        if (!digits_before && !digits_after) return 0;
    }
    if (i < len && (s[i] == 'e' || s[i] == 'E')) {
        size_t save = i;
        i++;
        if (i < len && (s[i] == '+' || s[i] == '-')) i++;
        int expdig = 0;
        while (i < len && isdigit((unsigned char)s[i])) { i++; expdig++; }
        if (!expdig) i = save;
    }
    if (!any) return 0;
    if (start > 0 && isalpha((unsigned char)s[start-1])) return 0;
    if (i < len && isalpha((unsigned char)s[i])) return 0;

    size_t L = i - start;
    char* tmp = (char*)malloc(L + 1);
    if (!tmp) return 0;
    for (size_t k = 0; k < L; ++k) {
        tmp[k] = (s[start + k] == ',') ? '.' : s[start + k];
    }
    tmp[L] = '\0';
    char* endptr = NULL;
    double val = strtod(tmp, &endptr);
    free(tmp);
    if (endptr == NULL) return 0;
    *out_start = start;
    *out_end = i;
    *out_val = val;
    return 1;
}

static void task3_find_and_print_numbers(const char* text, size_t len) {
    printf("Task 3: find numbers and bring them to the format\n");
    size_t i = 0;
    int found = 0;
    while (i < len) {
        size_t st=0, ed=0; double val = 0.0;
        if (parse_number_at(text, len, i, &st, &ed, &val)) {
            found = 1;
            char buf[64];
            snprintf(buf, sizeof(buf), "%.4f", val);
            printf("Orig: %.*s  ->  (%s)\n", (int)(ed-st), text+st, buf);
            i = ed;
        } else {
            i++;
        }
    }
    if (!found) printf("Numbers not found.\n");
}

//Task 4
static void task4_replace_dates_and_write(const char* text, size_t len) {
    time_t t = time(NULL);
    struct tm tmv;
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tmv, &t);
#else
    localtime_r(&t, &tmv);
#endif
    char curdate[32];
    snprintf(curdate, sizeof(curdate), "%04d-%02d-%02d", tmv.tm_year + 1900, tmv.tm_mon + 1, tmv.tm_mday);

    size_t cap = len * 3 + 100;
    char* out = (char*)malloc(cap);
    if (!out) { fprintf(stderr, "Memory error\n"); return; }
    size_t oi = 0;

    size_t i = 0;
    while (i < len) {
        size_t st=0, ed=0; int d=0,m=0,y=0;
        if (parse_date_at(text, len, i, &st, &ed, &d, &m, &y)) {
            while (i < st) {
                if (oi + 2 >= cap) { cap *= 2; out = (char*)realloc(out, cap); }
                out[oi++] = text[i++];
            }
            size_t cdlen = strlen(curdate);
            if (oi + cdlen + 2 >= cap) { cap = cap + cdlen + 100; out = (char*)realloc(out, cap); }
            memcpy(out + oi, curdate, cdlen); oi += cdlen;
            i = ed;
        } else {
            if (oi + 2 >= cap) { cap *= 2; out = (char*)realloc(out, cap); }
            out[oi++] = text[i++];
        }
    }
    out[oi] = '\0';

    FILE* fout = fopen(OUT_REPLACED, "wb");
    if (!fout) {
        fprintf(stderr, "Could not open %s for writing\n", OUT_REPLACED);
        free(out);
        return;
    }
    fwrite(out, 1, oi, fout);
    fclose(fout);
    printf("Task 4: All dates replaced by %s and written to %s \n", curdate, OUT_REPLACED);
    free(out);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Using: %s input.txt\n", argv[0]);
        return 1;
    }
    size_t len = 0;
    char* text = read_file(argv[1], &len);
    if (!text) return 1;

    // Task 1
    task1_links(text);

    // Task 2
    task2_find_and_print_dates(text, len);

    // Task 3
    task3_find_and_print_numbers(text, len);

    // Task 4
    task4_replace_dates_and_write(text, len);

    free(text);
    return 0;
}
