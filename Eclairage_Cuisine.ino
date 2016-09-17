class Cuisine{
public:   //public otherwise error: test::test private

 int i; // a variable
    int EtatBp;
    int B3;
    int Tps;
    int TpsS;
    
 Cuisine(int _TpsS){ //the constructor
   i=0;
  _TpsS=TpsS; 
 }
 
 int Ton(int _Tps){

    if(_Tps>0)
    {
        _Tps=_Tps-1;
    }
    return _Tps;
}


 int Etat(int _EtatBp,int _B3,int _Tps){
   

switch(_EtatBp) {
    case 0:
        if(_B3 ==1)
        {
        _EtatBp=1;
        }
        break;
    case 1:
        if(_B3 ==1)
        {
            if(_Tps<=50)
            {
                _EtatBp=0;
            }
            else
            {
            _EtatBp=2;
            }
        }
        break;
    case 2:
        _EtatBp=3;
        break;
    case 3:
        if(_B3 ==1)
        {
        _EtatBp=0;
        }
        break;
  }
    return _EtatBp;
   
}
}; 
//-------------------------------------------------------------------

int TpsEv=300;
int TpsHot=300;
int Cpt_BpHot=0;
int BpHot = 38; 
int EtatBpHot=0;
int BpEv = 40;
int EtatBpEv=0;
int SpotHot = 9;
int SpotEv = 10;

int Led13 = 13;
int val=0;
int B3[10];
int TpsSgen=50;

//-------------------------------------------------------------------

Cuisine myCuisine(TpsSgen);

void setup(){

  Serial.begin(9600);
  pinMode(BpHot, INPUT);
  pinMode(BpEv, INPUT);
  
  pinMode(SpotHot, OUTPUT);
  pinMode(SpotEv, OUTPUT);
  pinMode(Led13, OUTPUT);


}

void loop(){

// Appel Tempo

TpsHot=myCuisine.Ton(TpsHot);
Serial.println(TpsHot);


//one shot BpHot B3[2]
val = digitalRead(BpHot);

if(val==1){
    if(!B3[1])
    {
          B3[1] = 1.0;
          B3[2] = 1.0;
    }
    else
    {
          B3[2] = 0.0;
    }
}
else {
          B3[1] = 0.0;
          B3[2] = 0.0;
}

EtatBpHot=myCuisine.Etat(EtatBpHot,B3[2],TpsHot);
            if(B3[2]==1 & EtatBpHot==1)
            {
            TpsHot=300;
            } 
Serial.println(EtatBpHot);


TpsEv=myCuisine.Ton(TpsEv);
//Serial.println(TpsEv);
 
 //one shot BpEv B3[4]
 val = digitalRead(BpEv);
 
if(val==1){
    if(!B3[3])
    {
          B3[3] = 1.0;
          B3[4] = 1.0;      
    }
    else
    {
          B3[4] = 0.0;
    }
}
else {
          B3[3] = 0.0;
          B3[4] = 0.0;
}

EtatBpEv=myCuisine.Etat(EtatBpEv,B3[4],TpsEv);
            if(B3[4]==1 & EtatBpEv==1)
            {
            TpsEv=300;
            } 
//Serial.println(EtatBpEv);

          
            
// Actions sur les sorties
       if(EtatBpHot==1)
       {
       digitalWrite(SpotHot,HIGH);

       }
       if(EtatBpHot==3)
       {
       digitalWrite(SpotEv,HIGH);
       }
       if(EtatBpHot==0)
       {
       digitalWrite(SpotHot,LOW);

       }
   //----    
       if(EtatBpEv==1)
       {
       digitalWrite(SpotEv,HIGH);

       }
       if(EtatBpEv==3)
       {
       digitalWrite(SpotHot,HIGH);
       }
       
       if(EtatBpEv==0)
       {
       digitalWrite(SpotEv,LOW);

       }


}