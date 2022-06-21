#include <stdio.h>
#include <assert.h>
#define PRODUCTION_CODE_STDON   1
#define PRODUCTION_CODE_STDOFF  0
#define ENABLE_PRODUCTION_CODE  PRODUCTIONCODE_STDOFF

#define ALERT_THRESHOLD_LEVEL 200

int alertFailureCount = 0;

#if(ENABLE_PRODUCTION_CODE == PRODUCTIONCODE_STDOFF)
void Testalert_inCelcius(float celcius) {
        if (celcius < ALERT_THRESHOLD_LEVEL)
         {
             assert(networkAlertStub(celcius)==200);
         }
    else
        {
             assert(networkAlertStub(celcius)==500);
             assert(alertFailureCount != 0);    
        } 
}  
#endif

int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    // Return 200 for ok
    // Return 500 for not-ok
    // stub always succeeds and returns 200
    return 200;
}

void alertInCelcius(float farenheit) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlertStub(celcius);
    #if(ENABLE_PRODUCTION_CODE == PRODUCTIONCODE_STDON)
    if (returnCode != 200) {
        // non-ok response is not an error! Issues happen in life!
        // let us keep a count of failures to report
        // However, this code doesn't count failures!
        // Add a test below to catch this bug. Alter the stub above, if needed.
        alertFailureCount += 0;
    }
    #else
    Testalert_inCelcius(celcius);
#endif
}

int main() {
    alertInCelcius(400.5);
    alertInCelcius(303.6);
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
