/*
 * Copyright (C) 2006 Leo Osvald <leo.osvald@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 *
 * You may obtain a copy of the License at
 * 		http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdio>
#include <cmath>
#include <cstring>
typedef long long int ll;
const ll inf = 2147483647;
void bs(ll left, ll right) {
    int br = 1;
    ll mid;
    while(left <= right) {
        mid = (left+right)/2;
        printf("%d: Is it less or greater than %lld? ", br++, mid);
        char tmp[100];
        scanf("%s", tmp);
        if(!strcmp(tmp, "less") || !strcmp(tmp, "<")) right = mid-1;
        else left = mid+1;
    }
    printf("Hahaha, I guessed your number - it is %lld !", mid);
}
int main() {
    printf("Imagine a positive integer 0-2147483647 ...\n");
    printf("Now, I am going to guess that number in at most %lld guesses.\n",
     (ll) (log(inf)/log(2)+1));
    bs(0, inf);
    scanf("\n");
    return 0;
}
