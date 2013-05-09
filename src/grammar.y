%{

# from grammar.y - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech

#include <stdio.h>
#include <string.h>
#include "../headers/vectors.h"

extern FILE *yyin;
extern int linenum;
 
void yyerror(const char *str)
{
        fprintf(stderr,"error: %s at line %d\n",str, linenum);
}
 
int yywrap()
{
        return 1;
} 
  
int main(int argc, char *argv[])
{
    /* Call the lexer, then quit. */
    yyin=fopen(argv[1],"r");
    yyparse();
    fclose(yyin);
    return 0;
}  

%}

%union {
  double dValue;
  int iValue;
  Vec vValue;
}

%type <iValue> integer
%type <vValue> vector
%token <dValue> FLOAT


%token TOK_CAMERA TOK_OBJECT OPEN_CURLIES CLOSE_CURLIES TOK_AT TOK_DOWN OPENBRACKET TOK_CLOSEBRACKET TOK_LOOKAT TOK_WIDTH TOK_HEIGHT TOK_DEPTH TOK_RESOLUTION LIGHT COLOUR POSITION OBJECT MATERIAL DIFFUSE

%token SPHERE PLANE
%token CENTER RADIUS
%token NORMAL

%%
commands: /* empty */
        | commands command
        ;

command:
        camera_definition
        | light_definition
        | object_definition
        ;
        
object_definition:
        object_open object_commands CLOSE_CURLIES
        
object_open:
        OBJECT OPEN_CURLIES
        {
          printf("Encountered object OPEN\n");
        };
        
object_commands: /* empty */
       | object_commands object_command;
       
object_command:
      shape_definition
      | material_definition;
      
shape_definition:
     sphere_definition
     | plane_definition;
     
sphere_definition: 
    sphere_open sphere_commands CLOSE_CURLIES
    {
      printf("read a sphere definition\n");
    };
    
sphere_open:
    SPHERE OPEN_CURLIES
    {
      printf("opened a sphere\n");
    };
    
sphere_commands: /* empty */
    | sphere_commands sphere_command;
    
sphere_command:
    sphere_center_command
    | sphere_radius_command;
    
sphere_center_command:
    CENTER vector
    {
      printf("Defined Sphere Center\n");
    };
    
sphere_radius_command:
    RADIUS FLOAT
    {
      printf("Defined Sphere Radius\n");
    };
    
plane_definition:
   plane_open plane_commands CLOSE_CURLIES;
   
plane_open: 
    PLANE OPEN_CURLIES
   {
     printf("opened a plane\n");
   };
   
plane_commands: /* empty */
    | plane_commands plane_command;
    
plane_command:
   plane_position_command
   | plane_normal_command;
   
plane_position_command:
  POSITION vector
  {
    printf("defined a plane position vector\n");
  };
  
plane_normal_command:
  NORMAL vector
  {
    printf("defined the plane normal\n");
  };

material_definition:
  material_open material_commands CLOSE_CURLIES;
  
material_open:
  MATERIAL OPEN_CURLIES
  {
    printf("opened material definition\n");
  };
  
material_commands: /* empty */
  | material_commands material_command;
  
material_command:
  material_diffuse_command;
  
material_diffuse_command:
  DIFFUSE COLOUR vector
  {
    printf("defined diffuse colour\n");
  };
  
       
        
light_definition:
        light_open light_commands CLOSE_CURLIES
        {
          printf("Encountered a light defintiion\n");
        };
        
light_open:
        LIGHT OPEN_CURLIES
        {
          printf("opening light\n");
        };
        
light_commands: /* empty */
        | light_commands light_command
        ;
        
light_command:
        light_position_command
        |
        light_colour_command
        ;
        
light_position_command:
        POSITION vector
        {
          printf("light position\n");
        };

light_colour_command:
        COLOUR vector
        {
          printf("light colour\n");
        };

camera_definition:
        camera_open camera_commands CLOSE_CURLIES
        {
          printf("Encountered Camera Definition\n");
        };
        
camera_open:
        TOK_CAMERA OPEN_CURLIES
        {
          printf("Opened the camera\n");
        };
        
camera_commands: /* empty */
        | camera_commands camera_command
        ;
        
camera_command:
        cam_at_command
        |
        cam_down_command
        |
        cam_lookat_command
        |
        cam_width_command
        |
        cam_height_command
        |
        cam_depth_command
        |
        cam_resolution_command
        ;
        
cam_resolution_command:
        TOK_RESOLUTION OPENBRACKET cam_res_indeces TOK_CLOSEBRACKET;
        
cam_res_indeces:
        integer integer
        {
          printf("received a resolution command(%d %d)\n", $1, $2);
        };
        
cam_width_command:
        TOK_WIDTH FLOAT
        {
          printf("received camera width command\n");
        };
        
cam_height_command:
        TOK_HEIGHT FLOAT
        {
          printf("received camera height command\n");
        };
cam_depth_command:
        TOK_DEPTH FLOAT
        {
          printf("received camera depth command\n");
        };


cam_lookat_command:
        TOK_LOOKAT vector
        {
          printf("received a camera look at command\n");
        };

        
cam_at_command:
        TOK_AT vector
        {
          printf("received a camera AT command\n");
        };
        
cam_down_command:
       TOK_DOWN vector
       {
         printf("received a camera DOWN command\n");
       };
       
vector: OPENBRACKET FLOAT FLOAT FLOAT TOK_CLOSEBRACKET
      {
        printf("received a vector %f, %f, %f\n", $2, $3, $4);
      };
            
integer: FLOAT { $$ = (int)$1; printf("found integer %d\n", $$);} ;
      
  
