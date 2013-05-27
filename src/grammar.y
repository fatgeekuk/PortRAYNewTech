%{

/* from grammar.y - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/storage.h"
#include "../headers/optparse.h"

extern FILE *yyin;
extern int linenum;
 
rlNode *parserStack;
 
int filePtr; 
char **args;
int argCount;
int verbose = 1;
struct opt_str fn = {NULL, 0};
char *outputFilename;

struct opt_spec options[] = {
  {opt_help, "h", "--help", OPT_NO_METAVAR, OPT_NO_HELP, OPT_NO_DATA},
  
  {opt_store_1, "v", "--verbose", OPT_NO_METAVAR,
    "make lots of noise [default]", &verbose},
    
  {opt_store_0, "q", "--quiet", OPT_NO_METAVAR,
    "be vewwy quiet (I’m hunting wabbits)", &verbose},
    
  {opt_store_str, "o", "--output", "FILE", "write output to FILE", &fn},
  
  {OPT_NO_ACTION}
};

void yyerror(const char *str)
{
        fprintf(stderr,"error: %s at line %d\n",str, linenum);
}
 
int yywrap()
{
    int answer = 1;
    while(1){
      filePtr++;
      if (filePtr >= argCount) break;
      if (*args[filePtr] && args[filePtr] != fn.s){
        printf("opening %s\n", args[filePtr]);
        yyin=fopen(args[filePtr], "r");
        answer = 0;
      }
    }
    filePtr++;
    return answer;
} 

void reportError(char *message){
  fprintf(stderr, "error at line %d, %s\n", linenum, message);
}
  
int main(int argc, char *argv[])
{
    int i;
    argCount = argc;
    args = argv;
    
    rlInit();
    irInit();
    setupStorage();
    
    opt_basename(argv[0], '/');
    if (opt_parse("usage: %s [options] arg1 ...", options, argv) == 0) {
      fprintf(stderr, "%s [options] <scenefile> ... : at least 1 scene file required\n", argv[0]);
      exit(EXIT_FAILURE);
    }
    printf("noise level: %s\n", verbose ? "verbose" : "quiet");
    if (fn.s) {
      fn.s[0] = fn.s0;
      outputFilename = fn.s;
    }
    else
      outputFilename = "output.tga";
    
    for (i = 1; i < argc; ++i) {
      printf("i = %d, %d\n", i, argc);
      if (*argv[i] && argv[i] != fn.s){
        printf("QQ %s\n", argv[i]);
        filePtr = i; break;
      
      }
    }
    
    parserStack = rlCreateList();

    /* Call the lexer, then quit. */
    yyin=fopen(argv[filePtr],"r");
    yyparse();
    fclose(yyin);
    
    rlReclaimList(parserStack);
    
    render(&camera, sceneList);
    
    return 0;
}

void *currentParserNode(){
  return(parserStack->next->data);
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
        object_open object_commands object_close;
        
object_open:
        OBJECT OPEN_CURLIES
        {
          /* allocate an object and add it to the head of the parser stack */
          object *answer;
          answer = malloc(sizeof(object));
          if (answer == NULL){
            printf("unable to allocate object\n");
            exit(1);
          }
          rlAddDataToHead(parserStack, answer);
        };

object_close: CLOSE_CURLIES
        {
          object *answer;
          answer = (object *)rlPopDataFromHead(parserStack);
          rlAddDataToHead(sceneList, (void *)answer);
        }
        
object_commands: /* empty */
       | object_commands object_command;
       
object_command:
      shape_definition
      | material_definition;
      
shape_definition:
     sphere_definition
     | plane_definition;
     
sphere_definition: 
    sphere_open sphere_commands sphere_close
    {
      printf("read a sphere definition\n");
    };
    
sphere_open:
    SPHERE OPEN_CURLIES
    {
      /* allocate a sphere and place it on the parserStack */
      rlAddDataToHead(parserStack, allocSphere());
    };

sphere_close: CLOSE_CURLIES
    {
      /* remove the sphere from the parser stack and place it into the object definition. */
      sphere *sph;
      sph = (sphere *)rlPopDataFromHead(parserStack);
      
      sphPrepare((void *)sph);
      
      ((object *)currentParserNode())->gInfo = sph;
      ((object *)currentParserNode())->gType = &sphereGeomType;
    }
    
sphere_commands: /* empty */
    | sphere_commands sphere_command;
    
sphere_command:
    sphere_center_command
    | sphere_radius_command;
    
sphere_center_command:
    CENTER vector
    {
      vecCopy(&$2, &((sphere *)currentParserNode())->center);
    };
    
sphere_radius_command:
    RADIUS FLOAT
    {
      ((sphere *)currentParserNode())->radius = $2;
    };
    
plane_definition:
   plane_open plane_commands plane_close;
   
plane_open: 
    PLANE OPEN_CURLIES
   {
     rlAddDataToHead(parserStack, allocPlane());
   };
   
plane_close:
    CLOSE_CURLIES
    {
      /* remove the plane from the parser stack and place it into the object definition. */
      plane *pla;
      pla = (plane *)rlPopDataFromHead(parserStack);
    
      ((object *)currentParserNode())->gInfo = pla;
      ((object *)currentParserNode())->gType = &planeGeomType;
    }
   
plane_commands: /* empty */
    | plane_commands plane_command;
    
plane_command:
   plane_position_command
   | plane_normal_command;
   
plane_position_command:
  POSITION vector
  {
    vecCopy(&$2, &((plane *)currentParserNode())->position);
  };
  
plane_normal_command:
  NORMAL vector
  {
    vecCopy(&$2, &((plane *)currentParserNode())->normal);
  };

material_definition:
  material_open material_commands material_close;
  
material_close:
  CLOSE_CURLIES
  {
    Material *mat;
    mat = (Material *)rlPopDataFromHead(parserStack);

    ((object *)currentParserNode())->material = mat;  
  };
  
material_open:
  MATERIAL OPEN_CURLIES
  {
    rlAddDataToHead(parserStack, allocMaterial());
  };
  
material_commands: /* empty */
  | material_commands material_command;
  
material_command:
  material_diffuse_command;
  
material_diffuse_command:
  DIFFUSE COLOUR vector
  {
    vecCopy(&$3, &((Material *)currentParserNode())->diffuse_colour);
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
        camera_open camera_commands camera_close
        {
          printf("Encountered Camera Definition\n");
        };
        
camera_close:
        CLOSE_CURLIES {
          printf("  At     : "); vecPrint(&(camera.at)); printf("\n");
          printf("  Look at: "); vecPrint(&(camera.lookAt)); printf("\n");
          printf("  Down   : "); vecPrint(&(camera.down)); printf("\n");
          printf("  Width  : %f\n", camera.width);
          printf("  Height : %f\n", camera.height);
          printf("  Depth  : %f\n", camera.depth);
          printf("  resolution: (%d %d)\n", camera.resX, camera.resY);
          camValidate();
          printf("Closing Camera\n");
        }
        
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
          camera.resX = $1;
          camera.resY = $2;
        };
        
cam_width_command:
        TOK_WIDTH FLOAT
        {
          camera.width = $2;
        };
        
cam_height_command:
        TOK_HEIGHT FLOAT
        {
          camera.height = $2;
        };
cam_depth_command:
        TOK_DEPTH FLOAT
        {
          camera.depth = $2;
        };

cam_lookat_command:
        TOK_LOOKAT vector
        {
          vecCopy(&$2, &(camera.lookAt));
        };

        
cam_at_command:
        TOK_AT vector
        {
          vecCopy(&$2, &(camera.at));
        };
        
cam_down_command:
       TOK_DOWN vector
       {
          vecCopy(&$2, &(camera.down));
       };
       
vector: OPENBRACKET FLOAT FLOAT FLOAT TOK_CLOSEBRACKET
      {
        vecSet($2, $3, $4, &$$);
      };
            
integer: FLOAT { $$ = (int)$1; } ;
      
  
