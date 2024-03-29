#include <iostream>
#include <string>
#include <stdexcept>

#include "BrowserHistory.h"

using std::cout;
using std::endl;
using std::string;

static int testCount = 0;

template <typename T>
bool testAnswer(const string &nameOfTest, const T& received, const T& expected);
bool testAnswer(const string &nameOfTest, const string& received, const string& expected);


int main() {

  {
      // Test BrowserHistory class
      BrowserHistory browserHistory;

      testAnswer("Empty history test", browserHistory.currentUrl(), string(""));

      browserHistory.visitSite(string("http://www.cnn.com"), 1135299);
      testAnswer("visitSite test 1", browserHistory.currentUrl(), string("http://www.cnn.com"));
      testAnswer("visitSite test 2", browserHistory.currentPageSize(), size_t(1135299));

      browserHistory.visitSite(string("http://www.cnn.com/world"), 1325149);
      testAnswer("visitSite test 3", browserHistory.currentUrl(), string("http://www.cnn.com/world"));

      browserHistory.backButton();
      testAnswer("backButton test", browserHistory.currentUrl(), string("http://www.cnn.com"));
      testAnswer("backButton test 2", browserHistory.currentPageSize(), size_t(1135299));

      browserHistory.backButton();
      testAnswer("backButton test 3", browserHistory.currentUrl(), string("http://www.cnn.com"));

      browserHistory.forwardButton();
      testAnswer("forwardButton test 1", browserHistory.currentUrl(), string("http://www.cnn.com/world"));

      browserHistory.forwardButton();
      testAnswer("forwardButton test 2", browserHistory.currentUrl(), string("http://www.cnn.com/world"));

  }

  {
      // Test BrowserHistory class
      BrowserHistory browserHistory;

      browserHistory.readFile("desktop.txt");
      testAnswer("desktop.txt test", browserHistory.currentUrl(), string("https://en.wikipedia.org/wiki/International_Space_Station"));

      browserHistory.backButton();
      testAnswer("desktop.txt back button test", browserHistory.currentUrl(), string("https://en.wikipedia.org/wiki/NASA"));

      browserHistory.forwardButton();
      testAnswer("desktop.txt forward button test", browserHistory.currentUrl(), string("https://en.wikipedia.org/wiki/International_Space_Station"));

      browserHistory.forwardButton();
      testAnswer("desktop.txt forward button again test", browserHistory.currentUrl(), string("https://en.wikipedia.org/wiki/International_Space_Station"));

      browserHistory.visitSite(string("www.cnn.com"), 1000);
      testAnswer("visitSite test", browserHistory.currentUrl(), string("www.cnn.com"));
      testAnswer("visitSite test", browserHistory.currentPageSize(), size_t(1000));

      testAnswer("getHistoryLength() test", browserHistory.getHistoryLength(), size_t(4));
  }

  {
      // Test BrowserHistory class
      BrowserHistory browserHistory;

      browserHistory.readFile("mobile.txt");
      testAnswer("mobile.txt test", browserHistory.currentUrl(), string("http://www.binomial.info/"));
      testAnswer("mobile.txt backButton test", browserHistory.currentPageSize(), size_t(613454));
      testAnswer("mobile.txt getHistoryLength() test", browserHistory.getHistoryLength(), size_t(4));
  }

  return 0;
}


string trim(const string &s) {
  const string WHITESPACE = " \n\r\t\f\v";
  size_t start = s.find_first_not_of(WHITESPACE);
  if (start == string::npos)
    return string();
  string sleft(s.substr(start));
  size_t end = sleft.find_last_not_of(WHITESPACE);
  return (sleft.substr(0, end + 1));
}

bool testAnswer(const string &nameOfTest, const string& received, const string& expected) {
    if (trim(received) == trim(expected)) {
        cout << "PASSED " << nameOfTest << ": expected and received " << received << endl;
        return true;
    }
    cout << "FAILED " << nameOfTest << ": expected " << expected << " but received " << received << endl;
    return false;
}

template <typename T>
bool testAnswer(const string &nameOfTest, const T& received, const T& expected) {
    if (received == expected) {
        cout << "PASSED " << nameOfTest << ": expected and received " << received << endl;
        return true;
    }
    cout << "FAILED " << nameOfTest << ": expected " << expected << " but received " << received << endl;
    return false;
}
