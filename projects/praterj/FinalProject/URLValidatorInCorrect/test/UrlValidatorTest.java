import junit.framework.TestCase;

public class UrlValidatorTest extends TestCase {
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
        System.out.println("Java URL tester V1.0 - Jeremy Prater");
        System.out.println("======================================================");
        System.out.println();
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES | UrlValidator.ALLOW_LOCAL_URLS);
        for (ResultPair testURL : testURLs)
        {
            checkUrl(urlVal, testURL);
        }
    }
}
