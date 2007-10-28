import javax.microedition.lcdui.*;
import javax.microedition.midlet.MIDlet;
public class unlocker extends MIDlet implements CommandListener {
    Display display;
    Form form_log;
    TextField log_tf;
    List list;
    private final String moj_imei = "353512001269684";
    //komande
    final Command cmd_Izlaz = new Command("Izlaz", Command.EXIT, 1);
    final Command cmd_Login = new Command("Login", Command.SCREEN, 1);
    final Command cmd_Natrag = new Command("Natrag", Command.BACK, 1);
    public int hash(int code) {
        int curr = code;
        int high_PRIME = 999983, low_PRIME = 617, mid_PRIME = 7393;
        int itr = (code & 0x7) + 1;//0xa57c2
        int xor1 = 0x55555, xor2 = 0xa57c2, xor3 = 0x20093;
        for(int times = 0; times < itr; ++times) {
            if((curr ^ xor1) != curr) curr ^= xor1;
            else curr ^= ~xor1;
            curr *= low_PRIME;
            curr += 0x2342;
            curr %= high_PRIME;
            //if(curr % 13 > 5) curr = times*times ;
            if(times%3 != 0) curr ^= xor2;
            else if(times % 4 != 0) curr |= mid_PRIME;
            else curr ^= xor2 & curr & mid_PRIME;
                curr %= mid_PRIME;
                curr ^= xor3;
                curr *= mid_PRIME;
                curr %= high_PRIME;
                if(curr < 100)
                    curr *= mid_PRIME;
            }
        //if(curr >= MAX) printf("Error (code %d-> %d)\n", code, curr);
        return curr;
    }



public unlocker() {  
       
        
        form_log = new Form("Login");
        /*String tvoj_imei = null;
        if(tvoj_imei == null) tvoj_imei = System.getProperty("com.motorola.IMEI");
        if(tvoj_imei == null) tvoj_imei = System.getProperty("com.motorola.imei");
        if(tvoj_imei == null) tvoj_imei = System.getProperty("IMEI");
        if(tvoj_imei == null) tvoj_imei = System.getProperty("imei");
        if(tvoj_imei == null) tvoj_imei = System.getProperty("phone.IMEI");
        if(tvoj_imei == null) tvoj_imei = System.getProperty("phone.imei");
        
        if( System.getProperty("com.motorola.IMEI") != null)  
        if( System.getProperty("com.motorola.IMEI") == moj_imei ||
                System.getProperty("com.motorola.imei") == moj_imei 
                || System.getProperty("IMEI") == moj_imei
                || System.getProperty("imei") == moj_imei
                || System.getProperty("phone.IMEI") == moj_imei
                || System.getProperty("phone.imei") == moj_imei)*/
                 form_log.addCommand( cmd_Login );
        form_log.addCommand( cmd_Izlaz );
        //form_log.append( new StringItem("Imei: ", ""+tvoj_imei) ); 
        log_tf = new TextField("Code:", "", 6, TextField.NUMERIC);
        form_log.append( log_tf );
    }
    public void commandAction(Command com, Displayable dis) {
        if(com == cmd_Izlaz ) {
            notifyDestroyed();
        }
        else if(com == cmd_Login) {
            list = new List("Sifra:", Choice.IMPLICIT);
            list.addCommand( cmd_Natrag );
            list.append(""+ hash( Integer.parseInt( log_tf.getString() ) ) , null);
            display.setCurrent( list );
            list.setCommandListener(this);
        }
        else if(com == cmd_Natrag) {
            display.setCurrent(form_log);
            form_log.setCommandListener(this);
        }
    }
    public void startApp() {
        display = Display.getDisplay(this);
        display.setCurrent( form_log );
        form_log.setCommandListener(this);
    }
    public void pauseApp() {
    }
    public void destroyApp(boolean unc) {
        display.setCurrent((Displayable) null );
    }
}
