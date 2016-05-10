#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class planet {
    public:
        double position[2];
        double velocity[2];
        double mass;
        std::string name;
        planet(std::string planetname, double M, double x,double y, double vx, double vy);
        planet();
        double distance(planet other);
        void rk4method1(int N, int years);
        void verletmethod1(int N, int years);
};

planet::planet(std::string planetname, double M, double x, double y, double vx, double vy){
    name = planetname;
    mass = M;
    position[0]=x; //position in AU
    position[1] = y;
    velocity[0] = vx; //velocities in AU/yr
    velocity[1] = vy;
};

double planet::distance(planet other){
  double xdiff = position[0]-other.position[0];
  double ydiff = position[1]-other.position[1];
  double r = sqrt(xdiff*xdiff+ydiff*ydiff);
  return r;
};

void planet::rk4method1(int N, int years){
    cout<<"rk4method"<<endl;
    double PI = 3.141526535;
    double n = N;
    double h = 1/(1+n);
    std::string N_str = std::to_string(N);
    std::string yr_str = std::to_string(years);
    std::string filename = "rk4method1/"+name+"rk4" + "N" + N_str +"yr" + yr_str + ".csv";
    ofstream myfile (filename);

    if (myfile.is_open())
      {
        planet Sun("Sun",1,0,0,0,0);
        double t=0; //time in years
        double x = position[0];
        double vx = velocity[0];
        double y = position[1];
        double vy = velocity[1];
        double r;
        //double x1, vx1, y1, vy1;
        double k1x, k1vx, k1y,k1vy;
        double k2x, k2vx, k2y,k2vy;
        double k3x, k3vx, k3y,k3vy;
        double k4x, k4vx, k4y,k4vy;


        //cout << t<< x<< vx << y << vy<< "\n" ;
        myfile << t << ","<< x<< ","<< vx<< "," << y<< "," << vy<< "\n" ;
        for(int count = 0; count <= (years*N); count ++){
            r = distance(Sun);
            t = t + h;
            //k1
            k1x = h*vx;
            k1vx = -4*PI*PI*x*h/(r*r*r);
            k1y = h*vy;
            k1vy = -4*PI*PI*y*h/(r*r*r);

            //k2
            k2x = h*(vx+k1vx/2);
            k2vx = h*(-4*PI*PI)*(x+k1x/2)/(r*r*r);
            k2y = h*(vy+k1vy/2);
            k2vy = h*(-4*PI*PI)*(y+k1y/2)/(r*r*r);

            //k3
            k3x = h*(vx+k2vx/2);
            k3vx = h*(-4*PI*PI)*(x+k2x/2)/(r*r*r);
            k3y = h*(vy+k2vy/2);
            k3vy = h*(-4*PI*PI)*(y+k2y/2)/(r*r*r);

            //k4
            k4x = h*(vx+k3vx);
            k4vx = h*(-4*PI*PI)*(x+k3x)/(r*r*r);
            k4y = h*(vy+k3vy);
            k4vy = h*(-4*PI*PI)*(y+k3y)/(r*r*r);

            x = x + (k1x + 2*k2x + 2 * k3x + k4x)/6;
            vx = vx + (k1vx + 2*k2vx + 2 * k3vx + k4vx)/6;
            y = y + (k1y + 2*k2y + 2 * k3y + k4y)/6;
            vy = vy + (k1vy + 2*k2vy + 2 * k3vy + k4vy)/6;

            myfile << t << ","<< x<< ","<< vx<< "," << y<< "," << vy<< "\n" ;
            position[0] = x; //position in AU
            position[1] = y;
            velocity[0] = vx; //velocities in AU/yr
            velocity[1] = vy;
        }
        myfile.close();
        cout<<"Output to rkmethod1/..."<<endl;
        position[0] = x; //position in AU
        position[1] = y;
        velocity[0] = vx; //velocities in AU/yr
        velocity[1] = vy;
      }

}

void planet::verletmethod1(int N, int years){
    planet Sun("Sun",1,0,0,0,0);
    double PI = 3.141526535;
    double n = N;
    double h = 1/(1+n);
    std::string N_str = std::to_string(N);
    std::string yr_str = std::to_string(years);
    std::string filename = name+"verlet" + "N" + N_str +"yr" + yr_str + ".csv";
    ofstream myfile (filename);
    if (myfile.is_open()){
        double t = 0.0; //time in years
        double x = position[0];
        double vx =velocity[0];
        double y = position[1];
        double vy = velocity[1];
        double x1, vx1, y1, vy1, r;

        //cout << t<< x<< vx << y << vy<< "\n" ;
        myfile << t << ","<< x<< ","<< vx<< "," << y<< "," << vy<< "\n" ;
        for(int count = 0; count <= (years*N); count ++){
            r = distance(Sun);
            //cout<<r;
            t = t + h;
            x1 = x + h*vx - h*h*2*PI*PI*x/(r*r*r);
            vx1 = vx - 2*PI*PI*(x+x1)*h/(r*r*r);
            y1 = y + h*vy - h*h*2*PI*PI*y/(r*r*r);
            vy1 = vy - 2*PI*PI*(y+y1)*h/(r*r*r);
            x= x1;
            vx=vx1;
            y=y1;
            vy=vy1;
            myfile << t << ","<< x<< ","<< vx<< "," << y<< "," << vy<< "\n" ;
            position[0] = x; //position in AU
            position[1] = y;
            velocity[0] = vx; //velocities in AU/yr
            velocity[1] = vy;
        }
        myfile.close();
        cout<<"Output saved to "<<filename<<endl;
      }

}

class asystem{
        public:
            vector<planet> planlist;
            asystem();
            int size;
            double totmass;
            void addplanet(planet plan);
            void center(); //will automatically center masses at origin
            void verletmethod(int N, int years);
            void rk4method(int N, int years);

    };

asystem::asystem(){
    size = 0;
    totmass = 0.0;
}

void asystem::addplanet(planet plan){
    planlist.push_back(plan);
    size++;
    totmass += plan.mass;
};

void asystem::center(){
    double xtot=0;
    double ytot=0;
    int i;
    for(i=0; i < size ; i++){
        planet plan = planlist[i];
        xtot+= plan.position[0]*plan.mass;
        ytot+= plan.position[1]*plan.mass;
    }
    double xcom = xtot/totmass;
    double ycom = ytot/totmass;

    for(i=0; i < size ; i++){
        planet plan = planlist[i];
        plan.position[0]-xcom;
        plan.position[1]-ycom;
    }

};

void asystem::verletmethod(int N, int years){
    double PI = 3.141526535;
    double n = N;
    double h = 1/(1+n);
    int i,j;
    std::string N_str = std::to_string(N);
    std::string yr_str = std::to_string(years);
        double t = 0.0; //time in years
        for(int count = 0; count < (years*N); count ++){ //iterate through number of steps
            //cout << "count: "<<count;
            for(i=0; i < size ; i++){               //iterate through eachplanet once per step
               t = h*count;
               //cout<<"Main: "<< plan.name;
               std::string filename = "verlet2/sys"+planlist[i].name+"N"+N_str+"yr"+yr_str+"verlet.csv";
               ofstream myfile (filename, std::ios::app);
               double x1, y1, vx1, vy1, r;
//
               x1 = planlist[i].position[0] + h*planlist[i].velocity[0];
               y1 = planlist[i].position[1] + h*planlist[i].velocity[1];
               vx1 = planlist[i].velocity[0];
               vy1 = planlist[i].velocity[1];
                   for(j=0; j < size ; j++){     //for each other planet

                       if (i!=j){
                           planet plan2 = planlist[j];
                           r = planlist[i].distance(plan2);
                           x1 -= plan2.mass*h*h*2*PI*PI*(planlist[i].position[0]-plan2.position[0])/(r*r*r);
                           y1 -= plan2.mass*h*h*2*PI*PI*(planlist[i].position[1]-plan2.position[1])/(r*r*r);
//                           cout << "+"<<plan2.name<<endl;
//                           cout<<"change"<<h*h*2*PI*PI*(planlist[i].position[0]-plan2.position[0])/(r*r*r);
//                           cout <<"x1 after"<<x1<<endl;
                       }
                   }
                   for(j=0; j < size ; j++){     //for each other planet
                       if (i!=j){
                           planet plan2 = planlist[j];
                           //cout << "+"<<plan2.name<<endl;
                           r = planlist[i].distance(plan2);
                           //cout <<"vx1 before"<<vx1;
                           vx1 -= plan2.mass*2*PI*PI*(planlist[i].position[0]+x1-2*plan2.position[0])*h/(r*r*r);
                           //cout<<"change"<<4*PI*PI*(plan.position[0]-plan2.position[0])*h/(r*r*r);
                           //cout <<"vx1 after"<<vx1<<endl;
                           vy1 -= plan2.mass*2*PI*PI*(planlist[i].position[1]+y1-2*plan2.position[1])*h/(r*r*r);

                       }
               }
               planlist[i].position[0]=x1;
               planlist[i].position[1]=y1;
               planlist[i].velocity[0]=vx1;
               planlist[i].velocity[1]=vy1;
               myfile << t << ","<< x1 << ","<< vx1<< "," << y1<< "," << vy1<< "\n" ;
               //cout << t << ","<< x1 << ","<< vx1<< "," << y1<< "," << vy1<< "\n" ;
                myfile.close();

            }
        }
 cout<<"Output saved to verlet2/..."<<endl;
     }

void asystem::rk4method(int N, int years){
    double PI = 3.141526535;
    double n = N;
    double h = 1/(1+n);
    int i,j;
    std::string N_str = std::to_string(N);
    std::string yr_str = std::to_string(years);
        double t = 0.0; //time in years
        for(int count = 0; count < (years*N); count ++){ //iterate through number of steps
            //cout << "count: "<<count;
            for(i=0; i < size ; i++){               //iterate through eachplanet once per step
               t = h*count;
               //cout<<"Main: "<< plan.name;
               std::string filename = "rk4method2/sys"+planlist[i].name+"N"+N_str+"yr"+yr_str+"verlet.csv";
               ofstream myfile (filename, std::ios::app);
               double x1, y1, vx1, vy1, r;
//
               x1 = planlist[i].position[0] + h*planlist[i].velocity[0];
               y1 = planlist[i].position[1] + h*planlist[i].velocity[1];
               vx1 = planlist[i].velocity[0];
               vy1 = planlist[i].velocity[1];
                   for(j=0; j < size ; j++){     //for each other planet

                       if (i!=j){
                           planet plan2 = planlist[j];
                           r = planlist[i].distance(plan2);
                           x1 -= plan2.mass*h*h*2*PI*PI*(planlist[i].position[0]-plan2.position[0])/(r*r*r);
                           y1 -= plan2.mass*h*h*2*PI*PI*(planlist[i].position[1]-plan2.position[1])/(r*r*r);
//                           cout << "+"<<plan2.name<<endl;
//                           cout<<"change"<<h*h*2*PI*PI*(planlist[i].position[0]-plan2.position[0])/(r*r*r);
//                           cout <<"x1 after"<<x1<<endl;
                       }
                   }
                   for(j=0; j < size ; j++){     //for each other planet
                       if (i!=j){
                           planet plan2 = planlist[j];
                           //cout << "+"<<plan2.name<<endl;
                           r = planlist[i].distance(plan2);
                           //cout <<"vx1 before"<<vx1;
                           vx1 -= plan2.mass*2*PI*PI*(planlist[i].position[0]+x1-2*plan2.position[0])*h/(r*r*r);
                           //cout<<"change"<<4*PI*PI*(plan.position[0]-plan2.position[0])*h/(r*r*r);
                           //cout <<"vx1 after"<<vx1<<endl;
                           vy1 -= plan2.mass*2*PI*PI*(planlist[i].position[1]+y1-2*plan2.position[1])*h/(r*r*r);

                       }
               }
               planlist[i].position[0]=x1;
               planlist[i].position[1]=y1;
               planlist[i].velocity[0]=vx1;
               planlist[i].velocity[1]=vy1;
               myfile << t << ","<< x1 << ","<< vx1<< "," << y1<< "," << vy1<< "\n" ;
               //cout << t << ","<< x1 << ","<< vx1<< "," << y1<< "," << vy1<< "\n" ;
                myfile.close();

            }
        }
 cout<<"Output saved to verlet2/..."<<endl;
     }




//void publishvector (double* X, int N, std::string filename){
////print vector X of size N with name "filename"
//    ofstream myfile (filename);
//    if (myfile.is_open())
//      {
//        for(int count = 0; count < N; count ++){
//            myfile << X[count] << "\n" ;
//        }
//        myfile.close();
//      }

//};

int main()
{
    const double PI = 3.1415926535;
        planet Sun("Sun",1,0,0,0,0);
        planet Mercury("Mercury",1.2e-7, 0, .39,-9.960,0);
        planet Venus("Venus",2.4e-6,-.72,0,0,7.36);
        planet Earth("Earth",1.5e-6,1,0,0, 6.26);
        planet Mars("Mars",3.3e-7, 1.52, 0,0,5.06);
        planet Jupiter("Jupiter",9.5e-4, 0,5.20,-2.75,0);
        planet Saturn("Saturn",2.75e-4, 0,-9.54,2.04,0);
        planet Uranus("Uranus",4.4e-5, 19.19, 0,0,-1.43);
        planet Neptune("Neptune",5.1e-5, -30.06, 0,0,-1.14);
        planet Pluto("Pluto",5.6e-9, 39.53, 0,0,0.99);


    //cout << "N?" << endl; //size of matrix
    int N, i;
    N = 10;
    int years = 1;
    double h;
    //cin >> N;
    double n = N;
    h = 1/(n+1);
//    double *X = new double[N];
//    // initialize X array all elements = 2
//    for(i=0 ; i < N ; i++) {
//        X[i] = 2.0;}
//    std::string N_str = std::to_string(N);
//    std::string filename = "N" + N_str + ".txt";
//    publishvector(X,N,filename);

    //partbverlet
   if (false){
       //verlet for earth
       Earth.verletmethod1(100,5);

   }

   //partbRK4
   if (false){
       //rk4 for earth
       planet Earth("Earth",1.5e-6,1,0,0, 6.26);
       cout<<"hello"<<endl;
       Earth.rk4method1(100,5);
       cout<<"world"<<endl;
//       ofstream myfile ("earthrk4.csv");
//       if (myfile.is_open())
//         {

//           double t=0; //time in years
//           double x = Earth.position[0];
//           double vx = Earth.velocity[0];
//           double y = Earth.position[1];
//           double vy = Earth.velocity[1];
//           double r;
//           //double x1, vx1, y1, vy1;
//           double k1x, k1vx, k1y,k1vy;
//           double k2x, k2vx, k2y,k2vy;
//           double k3x, k3vx, k3y,k3vy;
//           double k4x, k4vx, k4y,k4vy;

//           //cout << t<< x<< vx << y << vy<< "\n" ;
//           myfile << t << ","<< x<< ","<< vx<< "," << y<< "," << vy<< "\n" ;
//           for(int count = 0; count < (years*N); count ++){
//               r = Sun.planet::distance(Earth);
//               t = t + h;
//               //k1
//               k1x = h*vx;
//               k1vx = -4*PI*PI*x*h/(r*r*r);
//               k1y = h*vy;
//               k1vy = -4*PI*PI*y*h/(r*r*r);

//               //k2
//               k2x = h*(vx+k1vx/2);
//               k2vx = h*(-4*PI*PI)*(x+k1x/2)/(r*r*r);
//               k2y = h*(vy+k1vy/2);
//               k2vy = h*(-4*PI*PI)*(y+k1y/2)/(r*r*r);

//               //k3
//               k3x = h*(vx+k2vx/2);
//               k3vx = h*(-4*PI*PI)*(x+k2x/2)/(r*r*r);
//               k3y = h*(vy+k2vy/2);
//               k3vy = h*(-4*PI*PI)*(y+k2y/2)/(r*r*r);

//               //k4
//               k4x = h*(vx+k3vx);
//               k4vx = h*(-4*PI*PI)*(x+k3x)/(r*r*r);
//               k4y = h*(vy+k3vy);
//               k4vy = h*(-4*PI*PI)*(y+k3y)/(r*r*r);

//               x = x + (k1x + 2*k2x + 2 * k3x + k4x)/6;
//               vx = vx + (k1vx + 2*k2vx + 2 * k3vx + k4vx)/6;
//               y = y + (k1y + 2*k2y + 2 * k3y + k4y)/6;
//               vy = vy + (k1vy + 2*k2vy + 2 * k3vy + k4vy)/6;

//               myfile << t << ","<< x<< ","<< vx<< "," << y<< "," << vy<< "\n" ;
//           }
//           myfile.close();
//         }
       }
   //end of partbrk4

   //part d escape velocity
   if (false){
        float v = 8.0; //AU/YR
        for(i=0; i < 11 ; i++){
            cout<<i;
            float vy = v+i*.1;
            std::string i_str = std::to_string(i);
            std::string planetname = "test"+i_str;
            planet test(planetname,1000,1,0,0,vy);
            test.rk4method1(100,pow(2,i));

        }





   };

    //part f

   if(true){
       asystem solar;

       solar.addplanet(Sun);
       solar.addplanet(Mercury);
       solar.addplanet(Venus);
       solar.addplanet(Earth);
       solar.addplanet(Mars);
       solar.addplanet(Jupiter);
       solar.addplanet(Saturn);
       solar.addplanet(Uranus);
       solar.addplanet(Neptune);
       solar.addplanet(Pluto);

       solar.center();
       cout<<"size"<<solar.size<<endl;
       solar.verletmethod(200,250);
   };
   system("pause");
}
