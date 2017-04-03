#include <time.h>
#include <stdio.h>

void GMtimeTest()
{

  
  time_t result;
  result = time(NULL);

  /* // converts time since epoch to a broken down time (Mon Apr 3 16:35:17 2017)
  cout << "result = " << result << endl;
  struct tm* brokentime = gmtime(&result);
  cout << "broken time = " << asctime(brokentime);
  */

  struct tm* brokentime = new tm();
  gmtime_r(&result, brokentime);
  cout << "result = " << result << endl;
  cout << asctime(brokentime) << endl;
  delete(brokentime);

  return;
  
}
