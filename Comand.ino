
//EX:F.3.
void command()  //分析command 
{
   
    RcvChar =Serial.read();
   Serial.println(RcvChar);
   // mySerial.write(RcvChar);
      commandReceived = true;   //確認serial port有無資料輸入
     
        if(RcvChar==',')        //EX:P.10.5.0.10
        {
          data[Command_counter]=InData;  //data[0]=M,data[1]=10,data[2]=5,data[3]=0,data[4]=10
          
          
          InData="";                     //InData 存入一組字串後clear
          Command_counter++;
        }else
        {
          InData += RcvChar;    //InData先後存入P=>10=>5=>0
       
         // Serial.write(RcvChar);
          delay(10);
        }
}
void process()                                      //接受資料完後執行動作
{
                             //Debug 顯示目前command
      //mySerial.println("Command_counter=");mySerial.println("\t");Serial.println(Command_counter);
      for(int i=0;i<Command_counter;i++)
      {
       Serial.println(data[i]);
      
      }
}
      
