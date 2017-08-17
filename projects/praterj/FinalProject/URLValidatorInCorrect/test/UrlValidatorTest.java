import junit.framework.TestCase;
import java.util.Random;

public class UrlValidatorTest extends TestCase {


    private static int MAX_TESTS = 20;//number of iterations to run of testIsValid
    private static int numParts = 2; //total number of parts

    //schemes
    static String validScheme[] = {"http://", "ftp://"};
    static String invalidScheme[] = {"hppt://", "ftp::/"};

    //authority
    static String validAuthority[] = {"www.google.com", "123.123.123.123"};
    static String invalidAuthority[] = {".abc@", "!@#", "123.123.123.400"};

    public static void valid_unittest(){
       //instantiate the validator
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

       //build the url to test from random valid parts
       String url = "";
       Random rand = new Random();
       int scheme = rand.nextInt(validScheme.length);
       int auth = rand.nextInt(validAuthority.length);
       url = validScheme[scheme] + validAuthority[auth];

       //1 in 4 chance of adding a port number to the string
       if(rand.nextInt(4) == 3)
       {
           int port = rand.nextInt(65536);//port number ranges 0-65535
           //url = url + "/:" + port;
           url = url + ":" + port;
       }

       //print out the url and test if valid
       System.out.print(url + " :  ");
       System.out.println(urlVal.isValid(url));

   }

   public static void invalid_unittest(){
        //instantiate the validator
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        //build the url to test from random valid parts
        String url = "";
        Random rand = new Random();
        int whichInvalid = rand.nextInt(numParts+1);//the "+1" is so ports can be tested
        int scheme;
        int auth;
        int port;

        switch(whichInvalid)
        {
            case 0:
                scheme = rand.nextInt(invalidScheme.length);
                auth = rand.nextInt(validAuthority.length);
                url = invalidScheme[scheme] + validAuthority[auth];
                break;
            case 1:
                scheme = rand.nextInt(validScheme.length);
                auth = rand.nextInt(invalidAuthority.length);
                url = validScheme[scheme] + invalidAuthority[auth];
                break;
            case 2:
                scheme = rand.nextInt(validScheme.length);
                auth = rand.nextInt(validAuthority.length);
                port = 65535 + rand.nextInt(10000);
                url = validScheme[scheme] + validAuthority[auth] + ":" + port;
                break;
        }

        //print out the url and test if valid
        System.out.print(url + " :  ");
	    System.out.println(urlVal.isValid(url));
   }
   public static void testIsValid(){
       for(int i = 0;i < MAX_TESTS; i++)
       {
           if (i == 0)
              System.out.println("***** The folowing URLs should test as true *****");

           if(i == MAX_TESTS/2)
              System.out.println("***** The folowing URLs should test as false *****");

           if(i < MAX_TESTS/2)
              valid_unittest();
           else
              invalid_unittest();
      }
  }

   static ResultPair[] testURLs = {
        ///////////////////////////////////////////////////////
        //
        // Testing Partition - Invalid SCHEMA
        //
        new ResultPair("http://", false),
        new ResultPair("ftp://!@#", false),
        new ResultPair("http://!@#", false),
        new ResultPair("ftp://!@#", false),
        new ResultPair("ftp://!@#", false),
        new ResultPair("http://.abc@", false),
        new ResultPair("http://.abc@", false),
        new ResultPair("http://!@#", false),
        new ResultPair("ftp://!@#", false),
        new ResultPair("http://.abc@", false),
        new ResultPair("http://!@#", false),

        ///////////////////////////////////////////////////////
        //
        // Testing Partition - IP Addresses
        //

        new ResultPair("http://123.123.123", false),
        new ResultPair("http://123.123.123.123", true),
        new ResultPair("http://123.123.123.123.123", false),
        new ResultPair("http://123.123.123.123:123", true),
        new ResultPair("http://123.123.123.123:1234", true),


        ///////////////////////////////////////////////////////
        //
        // Testing Partition - Domain Names
        //

        new ResultPair("http://google", false),
        new ResultPair("http://www.google.com", true),
        new ResultPair("http://www.google.com:808", true),
        new ResultPair("http://www.google.com:8080", true),

        ///////////////////////////////////////////////////////
        //
        // Testing Partition - URL Query
        //

        new ResultPair("http://www.google.com:80/test1", true),
        new ResultPair("http://www.google.com:80/test1?action", true),
        new ResultPair("http://www.google.com:80/test1?action=view", true),
        new ResultPair("http://www.google.com:80/test1?action=view&mode=up", true),

        ///////////////////////////////////////////////////////
        //
        // Testing Partition - Local URL testing
        //

        new ResultPair("http://freenas", true),
        new ResultPair("http://octprint/main", true),
   };
   private static boolean checkUrl(UrlValidator urlVal, ResultPair testURL) {
        boolean result = urlVal.isValid(testURL.item);
        if (result == testURL.valid) {
            System.out.print("[PASS] - ");
        }
        else {
            System.out.print("[FAIL] - ");

        }
        System.out.println(testURL.item);
        //assertEq(result, expectedResult);
        return result;
    }

    /**
    * Only used to debug the unit tests.
    * @param argv
    */
    public static void main(String[] argv) {
        System.out.println("======================================================");
        System.out.println("Java URL tester V1.0 - CS 362 Group Project");
        System.out.println("======================================================");
        System.out.println();
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES | UrlValidator.ALLOW_LOCAL_URLS);
        for (ResultPair testURL : testURLs)
        {
            checkUrl(urlVal, testURL);
        }
        System.out.println("Unit Tests:");
        testIsValid();
    }
}
