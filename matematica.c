float soma(float num1, float num2){
    return num1 + num2;
}

float sub(float num1, float num2){
    return num1 - num2;
}

float multi(float num1, float num2){
    return num1 *  num2;
}

float div(float num1, float num2){
    return num1 / num2;
}

float pow(float num1, float expo){
    while(expo > 1){
        num1 = multi(num1, num1);
        expo--;
    }
    return num1;
}

float sqrt(float n) {
    if (n < 0)
        return -1;

    if (n == 0)
        return 0;

    float x = n;
    float prev;
    float epsilon = 0.001f;

    do {
        prev = x;
        x = (x + n / x) / 2.0f;
    } while ((x - prev > epsilon) || (prev - x > epsilon));

    return x;
}


char *ordenadora(char *string){
    char i = *string;
    int tamanho = 0;
    int qtdParentenses = 0;
    while(i != '\0'){
        if(*(string + tamanho) == '(' || *(string + tamanho) == ')'){
            qtdParentenses++;
        }
        tamanho++;
        i = *(string + tamanho);
    }
   int asize = tamanho - qtdParentenses;
    char *ns = malloc((asize + 1) * sizeof(char));
    while(tamanho){
        
    }

}