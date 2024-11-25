int w_count(char *a){
    char *p = a;
    int count = 0;
    while(*p){
        if (*p != ' '){
            while(*p != ' '){
                if (*p == 0){
                    break;
                }
                p++;
            }
            count++;
        }
        else{
            p++;
        }
    }
    return count;
}

void sort(char **a, int n) {
  char **ult= &a[n-1];
  char **p= a;
  while (p<ult) {

    int x = w_count(p[0]);
    int y = w_count(p[1]);
    int t1 = x - y;

    if (t1 <= 0)
      p++;
    else {
      char *tmp= p[0];
      p[0]= p[1];
      p[1]= tmp;
      p= a;
    }
  }
}
