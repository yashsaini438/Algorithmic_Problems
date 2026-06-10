vector<int> makeSpf(int limit){

    vector<int> spf(limit+1,-1);

    spf[0] = 0;
    sfp[1] = 1;

    if(limit>=2)    spf[2] = 2;

    for(int i=4; i<=limit; i+=2){
        spf[i] = 2;
    }

    for(int i=3; i*i<= limit; i+=2){

        if(spf[i] == -1){

            // Optimized inner loop: start from i*i, step by 2*i to skip even numbers

            for(int j = i*i; j<= limit; j+= i*2){

                if(spf[j] == -1)    spf[j] = i;

            }
        }
    }

    // Fill remaining primes that are greater than sqrt(limit)
    for(int i=3; i<= limit; i+=2){

        if(spf[i] == -1){
            spf[i] = i;
        }

    }

    return spf;
}