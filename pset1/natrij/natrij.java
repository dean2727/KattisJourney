import java.util.Scanner;

class natrij {
    public static void main(String args[]) {
        // retrieve both lines of input
        Scanner input = new Scanner(System.in);
        String time1 = input.nextLine();
        String time2 = input.nextLine();
        input.close();

        Integer time1hr = Integer.parseInt(time1.substring(0, 2));
        Integer time1min = Integer.parseInt(time1.substring(3, 5));
        Integer time1sec = Integer.parseInt(time1.substring(6, 8));
        Integer time2hr = Integer.parseInt(time2.substring(0, 2));
        Integer time2min = Integer.parseInt(time2.substring(3, 5));
        Integer time2sec = Integer.parseInt(time2.substring(6, 8));

        Integer totalTimeSeconds = 0;

        /* if time1 is greater than time2, then we need to add the time from time1
        to midnight and then the time from midnight to time2 */
        if (time1hr > time2hr || (time1hr == time2hr && time1min > time2min) ||
        (time1hr == time2hr && time1min == time2min && time1sec > time2sec)) {

            if (time1sec != 0) {
                totalTimeSeconds += 60 - time1sec;
                time1min += 1;
            }
            if (time1min != 0) {
                totalTimeSeconds += 60 * (60 - time1min);
                time1hr += 1;
            }
            totalTimeSeconds += 60 * 60 * (24 - time1hr);

            totalTimeSeconds += time2sec + 60 * time2min + 60 * 60 * time2hr;
        }

        // else, just subtract time1 from time2
        else {
            if (time1sec != 0) {
                time1min += 1;
                totalTimeSeconds += 60 - time1sec;
            }
            if (time1min != 0) {
                time1hr += 1;
                totalTimeSeconds += 60 * (60 - time1min);
            }

            totalTimeSeconds += time2sec + 60 * time2min;

            totalTimeSeconds += 60 * 60 * (time2hr - time1hr);
        }

        // he wants at least 1 second, so if time1 = time2, make it be 1 second
        if (totalTimeSeconds / 60 / 60 == (totalTimeSeconds / 60) % 60 &&
        (totalTimeSeconds / 60) % 60 == totalTimeSeconds % 60) {
            System.out.print("24:00:00");
        }

        else {
            System.out.print(String.format("%02d", totalTimeSeconds / 60 / 60) + ":");  // num hours
            System.out.print(String.format("%02d", (totalTimeSeconds / 60) % 60) + ":");  // num minutes
            System.out.print(String.format("%02d", totalTimeSeconds % 60));  // num seconds
        }
    }
}
