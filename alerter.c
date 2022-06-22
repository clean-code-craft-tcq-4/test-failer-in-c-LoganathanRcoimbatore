#include <stdio.h>
#include <assert.h>

#define PRODUCTIONCODE_ON   1
#define PRODUCTIONCODE_OFF  0
#define ENABLE_PRODUCTION_CODE  PRODUCTIONCODE_OFF
int alertFailureCount = 0;

int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    // Return 200 for ok
    // Return 500 for not-ok
    // stub always succeeds and returns 200
    if(celcius<=200) {
        return 200;
    } else {
        return 500;
    }
}
void alertInCelcius(float farenheit) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlertStub(celcius);
    if (returnCode != 200) {
        // non-ok response is not an error! Issues happen in life!
        // let us keep a count of failures to report
        // However, this code doesn't count failures!
        // Add a test below to catch this bug. Alter the stub above, if needed.
        alertFailureCount += 0;
    }
}
int main() {
    alertInCelcius(400.5);
#if(ENABLE_PRODUCTION_CODE == PRODUCTIONCODE_OFF)
    assert(alertFailureCount == 1);
#endif
    alertInCelcius(392.0);
#if(ENABLE_PRODUCTION_CODE == PRODUCTIONCODE_OFF)
    assert(alertFailureCount == 1);
#endif
    alertInCelcius(303.6);
#if(ENABLE_PRODUCTION_CODE == PRODUCTIONCODE_OFF)
    assert(alertFailureCount == 0);
#endif
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
