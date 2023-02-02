import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class MessageEncoderDecoderImpl implements MessageEncoderDecoder<String> {

    private byte[] bytes = new byte[1 << 10]; //start with 1k
    private int len = 0;

    @Override
    public String decodeNextByte(byte nextByte) {
        if (nextByte == ';') {
            return popString();
        }
        pushByte(nextByte);
        return null;
    }
    public byte[] encode(String message){
        System.out.println("MESSAGE TO ENCODE: " + message);
        int index = 0;
        String first = message.substring(index,2);
        index += 2;
        String second = "";
        short opcodeClient = Short.parseShort(first);
        short opcodeServer;
        if(opcodeClient == 9){
            second += message.charAt(2);
            index++;
        }
        else{
            second = message.substring(index,4);
            index +=2;
        }
        opcodeServer = Short.parseShort(second);
        String zero = "\0";
        byte[] a = shortToBytes(opcodeClient);
        byte[] b = shortToBytes(opcodeServer);
        try(ByteArrayOutputStream outputStream = new ByteArrayOutputStream()) {
            outputStream.write(a);
            if (opcodeClient==9) {
                outputStream.write(opcodeServer);
            }
            else {
                outputStream.write(b);
            }
            //we have the first 2 shorts as bytes.
            if (opcodeServer==4){
                String userName = cutString(index,message);
                outputStream.write(userName.getBytes()); //uses UTF-8 by default.
                outputStream.write(zero.getBytes());
            }
            else if (opcodeServer==7 || opcodeServer==8) {
                while (index < message.length()-1) {
                    byte[] ans;
                    for (int i = 0; i < 3; i++) {
                        index++;
                        String len = cutString(index, message, ' ');
                        index += len.length();
                        ans = shortToBytes(Short.parseShort(len));
                        outputStream.write(ans);
                    }
                    index++;
                    String finalLen = cutString(index, message);
                    ans = shortToBytes(Short.parseShort(finalLen));
                    index += finalLen.length();
                    outputStream.write(ans);
                    }
            }
            if (opcodeClient==9) {
                String postingUser = cutString(index, message);
                index += postingUser.length() + 1;
                outputStream.write(postingUser.getBytes());
                outputStream.write(zero.getBytes());
                String content = cutString(index, message);
                outputStream.write(content.getBytes());
                outputStream.write(zero.getBytes());
            }
            outputStream.write(";".getBytes());
            byte[] byteArray=outputStream.toByteArray();
            return byteArray;
        } catch (IOException e) {
            e.printStackTrace();
        }

        return null; //won't happen
    }

    private void pushByte(byte nextByte) {
        if (len >= bytes.length) {
            bytes = Arrays.copyOf(bytes, len + 1);
        }

        bytes[len++] = nextByte;
    }

    private String popString() {
        //notice that we explicitly requesting that the string will be decoded from UTF-8
        //this is not actually required as it is the default encoding in java.
        byte[] opcode = new byte[2];
        opcode[0] = bytes[0];
        opcode[1] = bytes[1];
        short ops = bytesToShort(bytes);
        String result = Short.toString(ops);
        result += new String(bytes, 2, len-2, StandardCharsets.UTF_8);
        len = 0;
        if (ops<10) {
            result = "0" + result;
        }
        System.out.println("result- " + result);
        return result;
    }
    public short bytesToShort(byte[] byteArr)
    {
        short result = (short)((byteArr[0] & 0xff) << 8);
        result += (short)(byteArr[1] & 0xff);
        return result;
    }
    public byte[] shortToBytes(short num)
    {
        byte[] bytesArr = new byte[2];
        bytesArr[0] = (byte)((num >> 8) & 0xFF);
        bytesArr[1] = (byte)(num & 0xFF);
        return bytesArr;
    }

    private String cutString(int index,String string){
        String result = "";
        while (index<string.length() && string.charAt(index)!='\0') {
            result = result + string.charAt(index);
            index++;
        }
        return result;
    }
    private String cutString(int index,String string, char stop){
        String result = "";
        while (index<string.length() && string.charAt(index)!= stop){
            result += string.charAt(index);
            index++;
        }
        return result;
    }


}
