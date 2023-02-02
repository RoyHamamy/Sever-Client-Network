import java.nio.ByteBuffer;
import java.time.LocalDate;
import java.time.LocalTime;
import java.time.Period;
import java.time.ZonedDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Date;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.concurrent.BlockingDeque;
import java.util.concurrent.LinkedBlockingDeque;
import java.util.concurrent.LinkedBlockingQueue;

public class User {
    private String userName;
    private String password;
    private String birthday;
    private ConnectionHandler connectionHandler;
    private LinkedList<User> followList;
    private LinkedBlockingQueue<User> followedByList;
    private int postedMessages;
    private LinkedBlockingQueue<String> receivedMessages;
    private LinkedList<User> blockedList;
    private int followed = 0;

    public User(String userName, String password, String birthday) {
        this.userName = userName;
        this.password = password;
        this.birthday = birthday;
        this.followList = new LinkedList<>();
        this.postedMessages = 0;
        this.receivedMessages = new LinkedBlockingQueue<>();
        this.blockedList = new LinkedList<>();
        this.followedByList = new LinkedBlockingQueue<>();
    }

    public String getUserName() {
        return userName;
    }

    public String getPassword() {
        return password;
    }

    public String getBirthday() {
        return birthday;
    }

    public LinkedBlockingQueue<User> getFollowedByList() {
        return followedByList;
    }

    public ConnectionHandler getConnectionHandler() {
        return connectionHandler;
    }

    public void setConnectionHandler(ConnectionHandler connectionHandler) {
        this.connectionHandler = connectionHandler;
    }

    public LinkedList<User> getFollowList() {
        return followList;
    }

    public User findFollowUser(String username){
        Iterator ita = followList.iterator();
        while (ita.hasNext()){
            User user = (User) ita.next();
            if (user.getUserName().equals(username))
            return user;
        }
        return null;
    }


    public LinkedBlockingQueue<String> getReceivedMessages() {
        return receivedMessages;
    }

    public int getFollowed() {
        return followed;
    }

    public void increaseFollowed(){
        this.followed += 1;
    }

    public void decreaseFollowed(){
        this.followed -= 1;
    }

    public int getAge(){
        int birthYear = Integer.parseInt(this.getBirthday().substring(getBirthday().length()-4));
        ZonedDateTime curr_time = ZonedDateTime.now();
        int currYear = curr_time.getYear();
        int age = currYear - birthYear;
        int birthMonth = Integer.parseInt(this.getBirthday().substring(getBirthday().length()-7,getBirthday().length()-5));
        int currMonth = curr_time.getMonthValue();
        if(currMonth-birthMonth<0){
            age--;
        }
        return age;
    }

    public LinkedList<User> getBlockedList() {
        return blockedList;
    }

    public int getPostedMessages() {
        return postedMessages;
    }

    public void increasePostedMessages(){
        this.postedMessages += 1;
    }
}
