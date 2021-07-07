/******************************************* LIBRERIAS ****************************************************/

#include <windows.h>
#include <string.h>
#include <locale.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <queue>

/******************************************* VARIABLES GLOBALES ****************************************************/

#define a 30
#define MAX 40

int identificador;
int codigo_usuario_online;
int codigo_clase;
int clase[7];
char nombre_usuario_online[30];

using namespace std;

FILE * doc; 
FILE * notas;

/******************************************** ESTRUCTURAS ************************************************************/

struct clases
{
    int codigo_clase;
    char nombre[30];
};
typedef struct clases infoclases;
infoclases clas;

struct datos_alumnos_clases
{
	int codigo_alumno;
	int codigo_clase;
	int n1;
	int n2;
	int n3;
	int n4;
	float promedio;
};
typedef struct datos_alumnos_clases info_alum_clases;
info_alum_clases alum_clases;

struct maestros
{
	int codigo_maestro;
	char identidad[14];
    char contrasena[30];
    char nombre[30];
    char apellido[30];
    char profesion[50];
    int sueldo;
    int codigo_clase;
};
typedef struct maestros infomaestros;
infomaestros mas;

struct alumnos
{
	int codigo_alumno;
    char identidad[14];
    char contrasena[30];
    char nombre[30];
    char apellido[30];
    int grado;
    int codigo_clase[MAX];
};
typedef struct alumnos infoalumnos;
infoalumnos alum;

struct registro
{
	int codigo;
	char identidad[14];
	char nombre[30];
	char apellido[30];
    char contrasena[30];
};
typedef struct registro infore;
infore re;

/******************************************** PROTOTIPOS ************************************************************/

void login();
void usuario();
void contrasena();
void Administrador();
void ingresar_alumno();
void modificar_alumno();
void listar_alumno();
void ingresar_admin();
void modificar_admin();
void listar_admin();
void clases_default();
void listar_clase();
void ingresar_maestro();
void modificar_maestro();
void listar_maestro();
void Alumno();
void maestro();
void listado_alumnos();
void listado_notas(int, int);
void ingresar_nota(int);
void listar_promedio(int);
void ordenar_promedio(int, char[40][40], float[40]);
int Verificar_codigo_reg(int);
int Verificar_codigo_alum(int);
int Verificar_codigo_mas(int);
int Verificar_codigo_clase(char[30]);
int Validar_respuesta_numero(int , int , int);
int Validar_num_entero(char [30] , int , int );
char Validar_respuesta_letra(char, char, char);
char *Validar_respuesta_texto(char [30]);
char Validar_respuesta_repetir(char resp);
char * Verificar_identidad(char [14]);
char * Validar_contrasena(char [30]);
char * Validar_identidad(char [14]);

/* --- MAIN --- */

main(int argc, char *argv[])
{
	SetConsoleTitle("PROYECTO FINAL");
	setlocale(LC_CTYPE, "Spanish");
	
	login();
	return 0;
}

/******************************************** FUNCIONES ************************************************************/

/**************************************** FUNCIONES DE CONTEO ******************************************************/

// Función de conteo de registros de alumnos.

int c_alum(FILE * doc)
{
	int cont=0;
	doc=fopen("alumnos.dat","rb");
	fseek(doc,0,0);
	do
	{
		fread(&alum,sizeof(alum),1,doc);
		cont++;
	}
	while( !(feof(doc)) );
	fclose(doc);
	return cont-1;
}

// Función de conteo de registros de administradores.

int c_reg(FILE * doc)
{
	int cont=0;
	doc=fopen("registro.dat","rb");
	fseek(doc,0,0);
	do
	{
		fread(&re,sizeof(infore),1,doc);
		cont++;
	}
	while( !(feof(doc)) );
	fclose(doc);
	return cont-1;
}

// Función de conteo de registros de maestros.

int c_mas(FILE * doc)
{
	int cont=0;
	doc=fopen("maestros.dat","rb");
	fseek(doc,0,0);
	do
	{
		fread(&mas,sizeof(infomaestros),1,doc);
		clase[cont]=mas.codigo_clase;
		cont++;
	}
	while( !(feof(doc)) );
	fclose(doc);
	return cont-1;
}

// Función de conteo de registros de clases.

int c_clase(FILE * doc)
{
	int cont=0;
	doc=fopen("clases.dat","rb");
	fseek(doc,0,0);
	do
	{
		fread(&clas,sizeof(infoclases),1,doc);
		cont++;
	}
	while( !(feof(doc)) );
	fclose(doc);
	return cont-1;
}

// Función de conteo de registros de alum_clases.

int c_alum_clase(FILE * notas)
{
	int cont=0;
	notas=fopen("alumnos_clases.dat","rb");
	fseek(doc,0,0);
	do
	{
		fread(&alum_clases,sizeof(info_alum_clases),1,notas);
		cont++;
	}
	while( !(feof(notas)) );
	fclose(notas);
	return cont-1;
}

/************************************************* PANTALLAS *********************************************************/

// Pantalla Administrador.

void Administrador()
{
	char opc;
	do
	{
		system("cls");
		fflush(stdin);
		fflush(stdout);
		cout<<"\n\t\t\t--------------------------------------";
		cout<<"\n\t\t\t-              REGISTRO              -";
		cout<<"\n\t\t\t--------------------------------------";
		cout<<"\n\n\t\tUsuario: "<<codigo_usuario_online;
		cout<<"\n\t\tNombre: "<<nombre_usuario_online;
		cout<<"\n\n\t\t[A] . . . Ingresar/modificar/listar alumnos.";
		cout<<"\n\t\t[B] . . . Ingresar/modificar/listar maestros";
		cout<<"\n\t\t[C] . . . Ingresar/modificar/listar administrador.";
		cout<<"\n\t\t[D] . . . Listar clases.";
		cout<<"\n\t\t[E] . . . Cerrar sesión.";
		cout<<"\n\n\t\tIngrese su opción: ";
		cin>>opc;
		opc=toupper(opc);
		fflush(stdin);
		fflush(stdout);
		opc = Validar_respuesta_letra(opc, 'A', 'E');
		
		switch(opc)
		{
			case 'A':
			{
				do
				{
					int resp=0;
					char resp_char[30];
					system("cls");
					cout<<"\n\t\t\t--------------------------------------";
					cout<<"\n\t\t\t-          REGISTRO ALUMNOS          -";
					cout<<"\n\t\t\t--------------------------------------";
					cout<<"\n\n\t\t[1] . . . Ingresar alumno.";
					cout<<"\n\t\t[2] . . . Modificar alumno.";
					cout<<"\n\t\t[3] . . . Listar alumnos.";
					cout<<"\n\t\t[4] . . . Regresar al menú anterior."<<endl;
					cout<<"\n\t\tIngrese su opción: ";
					scanf("%s", &resp_char);
					fflush(stdin);
					resp = Validar_num_entero(resp_char, 1, 4);
					fflush(stdin);
					if(resp==1)
						ingresar_alumno();
						else if(resp==2)
							modificar_alumno();
							else if(resp==3)
								listar_alumno();
								else Administrador();
				}
				while(opc!=4);
				
				break;
			}
			case 'B':
			{
				do
				{
					int resp=0;
					char resp_char[30];
					system("cls");
					cout<<"\n\t\t\t--------------------------------------";
					cout<<"\n\t\t\t-          REGISTRO MAESTROS         -";
					cout<<"\n\t\t\t--------------------------------------";
					cout<<"\n\n\t\t[1] . . . Ingresar maestro.";
					cout<<"\n\t\t[2] . . . Modificar maestro.";
					cout<<"\n\t\t[3] . . . Listar maestros.";
					cout<<"\n\t\t[4] . . . Regresar al menú anterior."<<endl;
					cout<<"\n\t\tIngrese su opción: ";
					scanf("%s", &resp_char);
					fflush(stdin);
					resp = Validar_num_entero(resp_char, 1, 4);
					
					if(resp==1)
						ingresar_maestro();
						else if(resp==2)
							modificar_maestro();
							else if(resp==3)
								listar_maestro();
								else
									Administrador();
				}
				while(opc!=4);
				
				break;
			}
			case 'C':
				do
				{
					int resp=0;
					char resp_char[30];
					system("cls");
					cout<<"\n\t\t\t--------------------------------------";
					cout<<"\n\t\t\t-       REGISTRO ADMINISTRADOR       -";
					cout<<"\n\t\t\t--------------------------------------";
					cout<<"\n\n\t\t[1] . . . Ingresar administrador.";
					cout<<"\n\t\t[2] . . . Modificar administrador.";
					cout<<"\n\t\t[3] . . . Listar administradores.";
					cout<<"\n\t\t[4] . . . Regresar al menú anterior."<<endl;
					cout<<"\n\t\tIngrese su opción: ";
					scanf("%s", &resp_char);
					fflush(stdin);
					resp = Validar_num_entero(resp_char, 1, 4);
					fflush(stdin);
					
					if(resp==1) 
						ingresar_admin();
						else if(resp==2)
							modificar_admin();
							else if(resp==3)
								listar_admin();
								else
									Administrador();
				}
				while(opc!=4);
				
				break;
				
			case 'D':
				system("cls");
				listar_clase();
				cout<<"\n\n\t\t";
				system("pause");
			break;

			default:
				system("cls");
				login();
		}
	}
	while(opc!='E');
}

// Pantalla Alumnos

void Alumno()
{
	system("color 8f");
	
	char opc;
	
	do
	{
		system("cls");
		
		cout<<"\n\t\t\t--------------------------------------";
		cout<<"\n\t\t\t-              ALUMNOS               -";
		cout<<"\n\t\t\t--------------------------------------";
		
		cout<<"\n\n\t\tUsuario: "<<codigo_usuario_online;
		cout<<"\n\t\tNombre: "<<nombre_usuario_online;
		cout <<"\n\n\t\t[A] . . . Español";
		cout <<"\n\t\t[B] . . . Matemáticas";
		cout <<"\n\t\t[C] . . . Ciencias Naturales";
		cout <<"\n\t\t[D] . . . Ciencias Sociales";
		cout <<"\n\t\t[E] . . . Educacion Física";
		cout <<"\n\t\t[F] . . . Inglés";
		cout <<"\n\t\t[G] . . . Artística";
		cout <<"\n\t\t[H] . . . Cerrar sesión."<<endl;
		cout <<"\n\t\tIngrese su opción: ";
		cin>>opc;
		fflush(stdin);
		opc = toupper(opc);
		opc = Validar_respuesta_letra(opc, 'A', 'H');
		
		switch(opc)
		{
			case 'A':
				system ("cls");
				cout<<"\n\t\tESPAÑOL";
				cout<<"\n\t\t-------"<<endl;
				listado_notas(codigo_usuario_online, 1);
				break;
			case 'B':
				system ("cls");
				cout<<"\n\t\tMATEMÁTICAS";
				cout<<"\n\t\t-----------"<<endl;
				listado_notas(codigo_usuario_online, 2);
				break;
			case 'C':
				system ("cls");
				cout<<"\n\t\tCIENCIAS NATURALES";
				cout<<"\n\t\t-------- ---------"<<endl;
				listado_notas(codigo_usuario_online, 3);
				break;
				
			case 'D':
				system ("cls");
				cout<<"\n\t\tCIENCIAS SOCIALES";
				cout<<"\n\t\t-------- --------";
				listado_notas(codigo_usuario_online, 4);
				break;	
				
			case 'E':
				system ("cls");
				cout<<"\n\t\tEDUCACIÓN FÍSICA";
				cout<<"\n\t\t-------- --------"<<endl;
				listado_notas(codigo_usuario_online, 5);
				break;
			
			case 'F':
				system ("cls");
				cout<<"\n\t\tINGLÉS";
				cout<<"\n\t\t------"<<endl;
				listado_notas(codigo_usuario_online, 6);
				break;		
				
			case 'G':
				system ("cls");
				cout<<"\n\t\tARTÍSTICA";
				cout<<"\n\t\t---------"<<endl;
				listado_notas(codigo_usuario_online, 7);
				break;	
				
			default:
				system("cls");
				login();
				break;
		}	
	}
	while (opc!='H');
}

// Pantalla de maestros.

void maestro()
{
	system("color 8f");
	
	char opc;
	
	do
	{
		system ("cls");
		cout<<"\n\t\t\t--------------------------------------";
		cout<<"\n\t\t\t-              MAESTROS              -";
		cout<<"\n\t\t\t--------------------------------------";
		cout<<"\n\n\t\tUsuario: "<<codigo_usuario_online;
		cout<<"\n\t\tNombre: "<<nombre_usuario_online;
		cout<<"\n\t\tCodigo Clase: "<<codigo_clase;
		cout <<"\n\n\t\t[A] . . . Listado de alumnos.";
		cout <<"\n\t\t[B] . . . Ingresar nota.";
		cout <<"\n\t\t[C] . . . Consultar nota de alumno.";
		cout <<"\n\t\t[D] . . . Listar promedio.";
		cout <<"\n\t\t[F] . . . Cerrar sesión."<<endl;
		cout <<"\n\t\tIngrese su opcion: ";
		cin>>opc;
		opc=toupper(opc);
		fflush(stdin);
		fflush(stdout);
		opc = Validar_respuesta_letra(opc, 'A', 'F');
		
		switch(opc)
		{
			case 'A':
				listado_alumnos();
				break;
			case 'B':
			{
				int resp=0;
				do
				{
					int grado=0;
					char resp_char[30];
					
					system("cls");
					cout<<"\n\t\t\t--------------------------------------";
					cout<<"\n\t\t\t-          INGRESO DE NOTAS          -";
					cout<<"\n\t\t\t--------------------------------------";
					
					cout<<"\n\n\t\t[1] . . . Primer parcial.";
					cout<<"\n\t\t[2] . . . Segundo parcial.";
					cout<<"\n\t\t[3] . . . Tercer parcial.";
					cout<<"\n\t\t[4] . . . Cuarto parcial.";
					cout<<"\n\t\t[5] . . . Regresar al menú anterior."<<endl;
					cout<<"\n\t\tIngrese su opción: ";
					scanf("%s", &resp_char);
					fflush(stdin);
					resp = Validar_num_entero(resp_char, 1, 5);
					
					if(resp==1)
						ingresar_nota(1);
						else if(resp==2)
							ingresar_nota(2);
							else if(resp==3)
								ingresar_nota(3);
								else if(resp==4)
									ingresar_nota(4);
									else
										maestro();
				}
				while(resp!=5);
				break;
			}
			case 'C':
			{
				char codigo[30], resp;
				int cod, c, ca;
				bool bandera=false;
				system("cls");
				cout<<"\n\t\t\t--------------------------------------";
				cout<<"\n\t\t\t-          CONSULTAR NOTAS           -";
				cout<<"\n\t\t\t--------------------------------------";
				cout<<"\n\n\t\t\tIngrese el codigo del alumno: ";
				cin>>codigo;
				fflush(stdin);
				cod = Validar_num_entero(codigo, 1, 9999);
	
				fflush(stdin);
				doc=fopen("alumnos.dat","rb");
				fseek(doc,0,0);
				
				c=0;
				ca=c_alum(doc);
				while((!(feof(doc))) && (c<=ca))
				{
					fread(&alum,sizeof(alum),1,doc);
					if(cod==alum.codigo_alumno)
					{
						cout<<"\n\t\tIdentidad: "<<alum.identidad<<"\n\t\tNombre: "<<alum.nombre<<"\n\t\tApellido: "<<alum.apellido<<"\n\t\tGrado: "<<alum.grado;
						bandera=true;
						c=ca;
					}
					c++;
				}
				fclose(doc);
				
				fflush(stdin);
				
				if(bandera==false)
				{
					cout<<"\a\n\t\t¡Alumno no encontrado!"<<endl;
					cout<<"\n\t\t";
					system("pause");
				}
				else
				{
					cout<<"\n\n\t\t¿Desea proceder a visualizar las notas de este alumno? [S/N]: ";
					cin>>resp;
					resp=toupper(resp);
					resp=Validar_respuesta_repetir(resp);
					
					if (resp=='S')
					{
						listado_notas(cod, codigo_clase);
					}
					else
					{
						return;
					}
				}
				break;
			}
			case 'D':
			{
				int resp=0;
				do
				{
					
					int grado=0;
					char resp_char[30];
					
					system("cls");
					cout<<"\n\t\t\t--------------------------------------";
					cout<<"\n\t\t\t-          LISTAR PROMEDIO           -";
					cout<<"\n\t\t\t--------------------------------------";
					cout<<"\n\n\t\t[1] . . . Primer grado.";
					cout<<"\n\t\t[2] . . . Segundo grado.";
					cout<<"\n\t\t[3] . . . Tercer grado.";
					cout<<"\n\t\t[4] . . . Cuarto grado.";
					cout<<"\n\t\t[5] . . . Quinto grado.";
					cout<<"\n\t\t[6] . . . Sexto grado.";
					cout<<"\n\t\t[7] . . . Regresar al menú anterior."<<endl;
					cout<<"\n\t\tIngrese su opción: ";
					scanf("%s", &resp_char);
					fflush(stdin);
					resp = Validar_num_entero(resp_char, 1, 7);
					fflush(stdin);
					
					if(resp==1)
						listar_promedio(1);
					else if(resp==2)
						listar_promedio(2);
						else if(resp==3)
							listar_promedio(3);
							else if(resp==4)
								listar_promedio(4);
								else if(resp==5)
									listar_promedio(5);
									else if(resp==6)
										listar_promedio(6);
										else
											maestro();
				}while(resp!=7);
				
				break;
			}
			default:
				system("cls");
				login();
				break;
		}
	}
	while (opc!='F');		
}

/************************************************* LOGIN *********************************************************/

// Inicio de sesión.

void login()
{
	cout<<"\n\t\t\t--------------------------------------";
	cout<<"\n\t\t\t-          INICIO DE SESIÓN          -";
	cout<<"\n\t\t\t--------------------------------------";
	
	if ((doc = fopen("registro.dat","r+")) == NULL)
	{
    	doc = fopen("registro.dat","w+");
    	re.codigo=1; 
		strcpy (re.identidad, "0801200006012"); 
		strcpy (re.nombre, "ADMIN"); 
		strcpy (re.apellido, "ADMIN");
		strcpy (re.contrasena, "PASSWORD");
		fwrite(&re,sizeof(infore),1,doc);
    	cout<<"\n\n\t\tSe ha creado un usuario default.";
    }
    fclose(doc);
    
    if ((doc = fopen("alumnos.dat","r+")) == NULL)
    	doc = fopen("alumnos.dat","w+");
    fclose(doc);
    
    if ((doc = fopen("maestros.dat","r+")) == NULL)
    	doc = fopen("maestros.dat","w+");
    fclose(doc);
    
     if ((doc = fopen("clases.dat","r+")) == NULL)
    	clases_default();
    fclose(doc);
    
	usuario();
	contrasena();
}

// Función para crear clases por default.

void clases_default()
{
    int c=1;
    do
	{
        clas.codigo_clase=c;
        doc = fopen("clases.dat","ab");
        fseek(doc,0,SEEK_END);
        if(c==1)
		{
            strcpy(clas.nombre,"Espanol");
            fwrite(&clas,sizeof(infoclases),1,doc);
        }
		else
		{
            if(c==2)
			{
                strcpy(clas.nombre,"Matematicas");
                fwrite(&clas,sizeof(infoclases),1,doc);
            }
			else
			{
                if(c==3)
				{
                    strcpy(clas.nombre,"Ciencias Naturales");
                    fwrite(&clas,sizeof(infoclases),1,doc);
                }else
				{
                    if(c==4)
					{
                        strcpy(clas.nombre,"Ciencias Sociales");
                        fwrite(&clas,sizeof(infoclases),1,doc);
                    }
					else
					{
                        if(c==5)
						{
                            strcpy(clas.nombre,"Educacion Fisica");
                            fwrite(&clas,sizeof(infoclases),1,doc);
                        }
						else
						{
                            if(c==6)
							{
                                strcpy(clas.nombre,"Ingles");
                                fwrite(&clas,sizeof(infoclases),1,doc);
                            }
							else
							{
                                strcpy(clas.nombre,"Artistica");
                                fwrite(&clas,sizeof(infoclases),1,doc);
                            }
                        }
                    }
                }
            }
        }
        fclose(doc);
        c++;
    }
	while(c<=7);
}

// Función para la verificación del usuario.

void usuario()
{
	char usuario[a];
	int cantLog=0,cont,intentos=0;
	int contar;
	int posicion;
	bool val_usuario = false;
	
	do
	{
		system("color f0");
		
		cout<<"\n\n\t\tUsuario: ";
		cin>>usuario;
		
		doc = fopen("registro.dat","r+b");
    	fseek(doc,0,0);
       
    	contar=c_reg(doc);
    	cont = 0;
       
    	while((!(feof(doc)))&&(cont<contar))
    	{
			fread(&re,sizeof(infore),1,doc);
        	if(strcmp(re.identidad,usuario)==0)
			{
				codigo_usuario_online=re.codigo;
				strcpy(nombre_usuario_online,re.nombre);
				identificador=1;
        		system("color a0");
				Sleep(1000);
				cantLog=3;
				val_usuario=true;
				break;
        	}  
        	cont++;
    	}
		fflush(doc);
		fclose(doc);		
		fflush(stdin);
	
       doc = fopen("alumnos.dat","r+b");
       fseek(doc,0,0);
       
       contar=c_alum(doc);
       cont = 0;
       
       while((!(feof(doc)))&&(cont<contar))
    	{
			fread(&alum,sizeof(infoalumnos),1,doc);
        	if(strcmp(alum.identidad,usuario)==0)
			{
				codigo_usuario_online=alum.codigo_alumno;
				strcpy(nombre_usuario_online,alum.nombre);
				identificador=2;
        		system("color a0");
				Sleep(1000);
				cantLog=3;
				val_usuario=true;
				break;
        	}  
        	cont++;
    	}
		fflush(doc);
		fclose(doc);		
		fflush(stdin);
		
		doc = fopen("maestros.dat","r+b");
    	fseek(doc,0,0);
		
		contar=c_mas(doc);
    	cont = 0;
    	
    	while((!(feof(doc)))&&(cont<contar))
    	{
			fread(&mas,sizeof(infomaestros),1,doc);
        	if(strcmp(mas.identidad,usuario)==0)
			{
				codigo_usuario_online=mas.codigo_maestro;
				strcpy(nombre_usuario_online,mas.nombre);
				codigo_clase=mas.codigo_clase;
				identificador=3;
        		system("color a0");
				Sleep(1000);
				cantLog=3;
				val_usuario=true;
				break;
        	}  
        	cont++;
    	}
		fflush(doc);
		fclose(doc);		
		fflush(stdin);
		
		if(cantLog<2  && val_usuario == false)
		{
			system("color 40");
			cout<<"\a\n\t\t¡Error!, el usuario ingresado no existe. ";
			cout<<"\n\n\t\tIntento ["<<intentos+1; cout<<"/3].";
			intentos++;
			Sleep(1000);
		}
		cantLog++;	
	}
	while(cantLog<3);
	
	if(val_usuario == false)
	{
		system("color 40");
		printf("\a\n\n\t\t\tYa no tienes intentos.");
		Sleep(1000);
		system("cls");
		cout<<"\a\n\t\t\t          ¡ACCESO DENEGADO!";
		exit(0);
	}
}

// Verificación de la contraseña.

void contrasena()
{
	char contrasena[a];
	int j=0, cantLog=0, cont=0, intentos=0;
	int contar;
	bool val_contrasena = false;

	do
	{
		system("color f0");
		cout<<"\n\t\tContraseña: ";
			
		j=0;

		while(contrasena[j] != 13)
		{
			contrasena[j]=getch();
			
			if(contrasena[j] > 32 && j < 20)
			{
				putchar(42);
				j++;
			}
			else if(contrasena[j]==8 && j>0)
			{
				putchar(8);
				putchar(' ');
				putchar(8);
				j--;	
			}
		}
		
		contrasena[j] = '\0';
		fflush(stdin);
		
		if (identificador==1)
		{			
			contar = c_reg(doc);
			cont = 0;
			
			doc=fopen("registro.dat","r");
			rewind(doc);
			
			while((!(feof(doc)))&&(cont<contar))
	    	{
				fread (&re,sizeof(infore),1,doc);
	        	if(strcmp(re.contrasena,contrasena)==0)
				{
					system("color a0");
					Sleep(1000);
					cantLog=3;
					system("color f0");
					val_contrasena = true;
					Administrador();
					break;	
	        	}  
	        	cont++;
	    	}
	    	fflush(doc);
			fclose(doc);
			fflush(doc);
		}
		else if (identificador==2)
		{
			contar = c_alum(doc);
			cont = 0;
			
			doc=fopen("alumnos.dat","r");
			rewind(doc);
			
			while((!(feof(doc)))&&(cont<contar))
	    	{
				fread (&alum,sizeof(infoalumnos),1,doc);
	        	if(strcmp(alum.contrasena,contrasena)==0)
				{
					system("color a0");
					Sleep(1000);
					cantLog=3;
					system("color f0");
					val_contrasena = true;
					Alumno();
					break;	
	        	}  
	        	cont++;
	    	}
	    	fflush(doc);
			fclose(doc);
			fflush(doc);		
		}
		else
		{
			contar = c_mas(doc);
			cont = 0;
		
			doc=fopen("maestros.dat","r");
			rewind(doc);
		
			while((!(feof(doc)))&&(cont<contar))
    		{
				fread(&mas,sizeof(infomaestros),1,doc);
	        	if(strcmp(mas.contrasena,contrasena)==0)
				{
					system("color a0");
					Sleep(1000);
					cantLog=3;
					system("color f0");
					val_contrasena = true;
					maestro();
					break;	
	        	}  
	        	cont++;
    		}
    		fflush(doc);
			fclose(doc);
			fflush(doc);
		}

		if(cantLog<2 && val_contrasena == false)
		{
			system("color 40");
			cout<<"\a\n\n\t\t¡Error!, la contrasena ingresada es incorrecta. \n\n\t\tIntento ["<<intentos+1; cout<<"/3]."<<endl;
			intentos++;
			Sleep(1000);
		}
		cantLog++;
	}
	while(cantLog<3);
	
	if(val_contrasena == false)
	{
		system("color 40");
		printf("\a\n\n\t\t\tYa no tienes intentos.");
		Sleep(1000);
		system("cls");
		cout<<"\a\n\t\t\t          ¡ACCESO DENEGADO!";
		exit(0);
	}	
}

/************************************* FUNCIONES PARA INGRESAR *******************************************************/

// Función para ingresar administradres.

void ingresar_admin()
{
	int codigo=0;
	char identidad[14], resp, contrasena[30], codigo_char[30];
	
	do
	{
		system("cls");
		fflush(stdin);
		cout<<"\n\t\t\t--------------------------------------";
		cout<<"\n\t\t\t-       INGRESAR ADMINISTRADORES     -";
		cout<<"\n\t\t\t--------------------------------------";
		cout<<"\n\n\t\tCódigo: ";
		cin>>codigo_char;
		codigo = Validar_num_entero(codigo_char, 1, 9999);
		fflush(stdin);
		fflush(stdout);
		codigo = Verificar_codigo_reg(codigo);
		re.codigo=codigo;
		fflush(stdin);
		
		do
		{
			cout<<"\n\t\tIdentidad: ";
			cin>>identidad;
			fflush(stdin);
			strcpy(identidad, Validar_identidad(identidad));
			
			if(strlen(identidad) == 13)
				strcpy(re.identidad, Verificar_identidad(identidad));
				else
					cout<<"\a\n\t\t¡Error!, ingrese el número de identidad de nuevo."<<endl;
		}
		while (strlen(identidad)!=13);
		
		re.codigo=codigo;
		cout<<"\n\t\tNombre: ";
		gets(re.nombre);
		strupr(re.nombre);
		strcpy(re.nombre, Validar_respuesta_texto(re.nombre));
		cout<<"\n\t\tApellido: ";
		gets(re.apellido);
		strupr(re.apellido);
		strcpy(re.apellido, Validar_respuesta_texto(re.apellido));
		cout<<"\n\t\tContraseña: ";
		gets(contrasena);
		fflush(stdin);
		strcpy(re.contrasena, Validar_contrasena(contrasena));
		doc=fopen("registro.dat","ab");
		fseek(doc,0,SEEK_END);
		fwrite(&re,sizeof(infore),1,doc);
		fclose(doc);
		
		cout<<"\n\t\t¿Desea ingresar otro administrador? [S/N]: ";
		cin>>resp;
		resp=toupper(resp);	
		resp=Validar_respuesta_repetir(resp);
		
	}
	while (resp=='S');	
}

// Función para ingresar maestros;

void ingresar_maestro()
{
	int codigo=0, codigo_clas=0, ca;
	char sueldo[30], identidad[14], resp, contrasena[30], resp2, codigo_char[30], codigo_clas_char[30];
	
	do
	{
		ca=c_mas(doc);
		system("cls");
		fflush(stdin);
		cout<<"\n\t\t\t--------------------------------------";
		cout<<"\n\t\t\t-          INGRESAR MAESTROS         -";
		cout<<"\n\t\t\t--------------------------------------";
		cout<<"\n\n\t\tCódigo: ";
		cin>>codigo_char;
		codigo = Validar_num_entero(codigo_char, 1, 9999);
		fflush(stdin);
		codigo = Verificar_codigo_mas(codigo);
		mas.codigo_maestro = codigo;
		fflush(stdin);
		
		do
		{
			cout<<"\n\t\tIdentidad: ";
			cin>>identidad;
			fflush(stdin);
			strcpy(identidad, Validar_identidad(identidad));
			if ((strlen(identidad)==13))
				strcpy(mas.identidad, Verificar_identidad(identidad));
			else
			{
				cout<<"\a\n\t\t¡Error!, ingrese el número de identidad de nuevo."<<endl;
			}
		}
		while (strlen(identidad)!=13);
		
		mas.codigo_maestro=codigo;
		cout<<"\n\t\tNombre: ";
		gets(mas.nombre);
		strupr(mas.nombre);
		strcpy(mas.nombre, Validar_respuesta_texto(mas.nombre));
		cout<<"\n\t\tApellido: ";
		gets(mas.apellido);
		strupr(mas.apellido);
		strcpy(mas.apellido, Validar_respuesta_texto(mas.apellido));
		cout<<"\n\t\tContraseña: ";
		gets(contrasena);
		strcpy(mas.contrasena, Validar_contrasena(contrasena));
		fflush(stdin);
		cout<<"\n\t\tProfesión: ";
		gets(mas.profesion);
		strupr(mas.profesion);
		strcpy(mas.profesion, Validar_respuesta_texto(mas.profesion));
		fflush(stdin);
		listar_clase();
		cout<<"\n\n\t\tClase a impartir: ";
		cin>>codigo_clas_char;
		codigo_clas=Verificar_codigo_clase(codigo_clas_char);
		mas.codigo_clase=codigo_clas;
		fflush(stdin);
		cout<<"\n\t\tSueldo: ";
		cin>>sueldo;
		mas.sueldo = Validar_num_entero(sueldo, 8000, 25000);
		fflush(stdin);
		
		doc=fopen("maestros.dat","ab");
		fseek(doc,0,SEEK_END);
		fwrite(&mas,sizeof(infomaestros),1,doc);
		fclose(doc);
		
		cout<<"\n\t\tDesea ingresar otro maestro [S/N]: ";
		cin>>resp;
		resp=toupper(resp);	
		resp=Validar_respuesta_repetir(resp);	
	}
	while (resp=='S');		
}

// Función para ingresar alumnos.

void ingresar_alumno()
{
	int i, codigo=0;
	char grado[30], identidad[14], resp, contrasena[30], codigo_char[30];
	
	do
	{
		system("cls");
		fflush(stdin);
		cout<<"\n\t\t\t--------------------------------------";
		cout<<"\n\t\t\t-          INGRESAR ALUMNOS          -";
		cout<<"\n\t\t\t--------------------------------------";
		cout<<"\n\n\t\tCódigo: ";
		cin>>codigo_char;
		codigo = Validar_num_entero(codigo_char, 1, 9999);
		fflush(stdin);
		codigo = Verificar_codigo_alum(codigo);
		alum.codigo_alumno=codigo;
		fflush(stdin);
		
		do
		{
			cout<<"\n\t\tIdentidad: ";
			cin>>identidad;
			fflush(stdin);
			strcpy(identidad, Validar_identidad(identidad));
			if ((strlen(identidad)==13))
				strcpy(alum.identidad, Verificar_identidad(identidad));
			else
			{
				cout<<"\a\n\t\t¡Error!, ingrese el número de identidad de nuevo."<<endl;
			}
		}
		while (strlen(identidad)!=13);
		
		alum.codigo_alumno=codigo;
		cout<<"\n\t\tNombre: ";
		gets(alum.nombre);
		strupr(alum.nombre);
		strcpy(alum.nombre, Validar_respuesta_texto(alum.nombre));
		cout<<"\n\t\tApellido: ";
		gets(alum.apellido);
		strupr(alum.apellido);
		strcpy(alum.apellido, Validar_respuesta_texto(alum.apellido));
		cout<<"\n\t\tGrado: ";
		scanf ("%s", &grado);
		alum.grado = Validar_num_entero(grado, 1, 6);
		fflush(stdin);
		cout<<"\n\t\tContraseña: ";
		gets(contrasena);
		strcpy(alum.contrasena, Validar_contrasena(contrasena));
		fflush(stdin);
	
		for(i=0;i<7;i++)
			alum.codigo_clase[i]=i+1;

		doc=fopen("alumnos.dat","ab");
		fseek(doc,0,SEEK_END);
		fwrite(&alum,sizeof(alum),1,doc);
		fclose(doc);
		
		for(int j=0; j<7; j++)
		{
			alum_clases.codigo_alumno=alum.codigo_alumno;
			alum_clases.codigo_clase=j+1;
			doc=fopen("alumnos_clases.dat","ab");
			fseek(doc,0,SEEK_END);
			fwrite(&alum_clases,sizeof(info_alum_clases),1,doc);
			fclose(doc);
		}
		
		cout<<"\n\t\t¿Desea ingresar otro alumno? [S/N]: ";
		cin>>resp;
		resp=toupper(resp);	
		resp=Validar_respuesta_repetir(resp);
	}
	while (resp=='S');
}

// Función para ingresar notas.

void ingresar_nota(int n)
{
	char resp;
	
	do
	{
		char nota[10], codigo[30];
		bool bandera=false;
		int c=1, ca, cod;
		
		system("cls");
		fflush(stdin);
		fflush(stdout);
		ca=c_alum(doc); 
		cout<<"\n\t\t\t--------------------------------------";
		cout<<"\n\t\t\t-          INGRESO DE NOTAS          -";
		cout<<"\n\t\t\t--------------------------------------";
		cout<<"\n\n\t\tCódigo del alumno a ingresar nota: ";
		cin>>codigo;
		cod = Validar_num_entero(codigo, 1, 9999);
		fflush(stdin);
		doc=fopen("alumnos.dat","rb");
		fseek(doc,0,0);
		
		while((!(feof(doc))) && (c<=ca))
		{
			fread(&alum,sizeof(alum),1,doc);
			if(cod==alum.codigo_alumno)
			{
				cout<<"\n\t\tIdentidad: "<<alum.identidad<<"\n\t\tNombre: "<<alum.nombre<<"\n\t\tApellido: "<<alum.apellido<<"\n\t\tGrado: "<<alum.grado;
				bandera=true;
				c=ca;
			}
			c++;
		}
		fclose(doc);
		
		fflush(stdin);
		
		if(bandera==false)
		{
			cout<<"\a\n\t\t¡Alumno no encontrado!"<<endl;
		}
		else
		{
			cout<<"\n\n\t\t¿Desea proceder a ingresar la nota de este alumno? [S/N]: ";
			cin>>resp;
			resp=toupper(resp);
			resp=Validar_respuesta_repetir(resp);
			
			if (resp=='S')
			{
				fflush(stdin);
				doc=fopen("alumnos_clases.dat","r+b");
				fseek(doc,0,0);
				while( (!(feof(doc))) )
				{
					fread(&alum_clases,sizeof(info_alum_clases),1,doc);
					if(cod==alum_clases.codigo_alumno && codigo_clase==alum_clases.codigo_clase)
					{
						if(n==1)
						{
							cout<<"\n\t\tNota primer parcial: ";
							cin>>nota;
							alum_clases.n1 = Validar_num_entero(nota, 0, 100);
						}else if(n==2){
							cout<<"\n\t\tNota segundo parcial: ";
							cin>>nota;
							alum_clases.n2 = Validar_num_entero(nota, 0, 100);
						}else if(n==3){
							cout<<"\n\t\tNota tercer parcial: ";
							cin>>nota;
							alum_clases.n3 = Validar_num_entero(nota, 0, 100);
						}else{
							cout<<"\n\t\tNota cuarto parcial: ";
							cin>>nota;
							alum_clases.n4 = Validar_num_entero(nota, 0, 100);
						}
						alum_clases.promedio=float( (alum_clases.n1 + alum_clases.n2 + alum_clases.n3 + alum_clases.n4) )/4; //calculo de promedio
						int pos=ftell(doc)-sizeof(alum_clases);
						fseek(doc,pos,SEEK_SET);
						fwrite(&alum_clases,sizeof(info_alum_clases),1,doc);
						break;
					}
				}
				fclose(doc);
			}
			else
				return;
		}
		cout<<"\n\t\t¿Desea proceder a ingresar la nota de otro alumno? [S/N]: ";
		cin>>resp;
		resp=toupper(resp);
		resp=Validar_respuesta_repetir(resp);
		
	}while(resp=='S');
}

/************************************* FUNCIONES PARA MODIFICAR *******************************************************/

// Función para modificar administradores.

void modificar_admin()
{
	char resp, contrasena[30], codigo[30], identidad[14];
	bool bandera=false;
	int c=1, ca, cod;
	
	system("cls");
	fflush(stdin);
	fflush(stdout);
	ca=c_reg(doc); 
	cout<<"\n\t\t\t--------------------------------------";
	cout<<"\n\t\t\t-      MODIFICAR ADMINISTRADOR       -";
	cout<<"\n\t\t\t--------------------------------------";
	cout<<"\n\n\t\tCódigo del administrador a modificar: ";
	cin>>codigo;
	cod = Validar_num_entero(codigo, 1, 9999);
	fflush(stdin);
	doc=fopen("registro.dat","rb");
	fseek(doc,0,0);
	
	while((!(feof(doc))) && (c<=ca))
	{
		fread(&re,sizeof(infore),1,doc);
		if(cod==re.codigo)
		{
			cout<<"\n\t\tIdentidad: "<<re.identidad<<"\n\t\tNombre: "<<re.nombre<<"\n\t\tApellido: "<<re.apellido<<"\n\t\tContraseña: "<<re.contrasena;
			bandera=true;
			c=ca;
		}
		c++;
	}
	fclose(doc);
	
	fflush(stdin);
	
	if(bandera==false)
	{
		cout<<"\a\n\t\t¡Administrador no encontrado!"<<endl;
		cout<<"\n\t\t";
		system("pause");
	}
	else
	{
		cout<<"\n\n\t\t¿Desea proceder a modificar este administrador? [S/N]: ";
		cin>>resp;
		resp=toupper(resp);
		resp=Validar_respuesta_repetir(resp);
		
		if (resp=='S')
		{
			fflush(stdin);
			doc=fopen("registro.dat","r+b");
			fseek(doc,0,0);
			while( (!(feof(doc))) )
			{
				fread(&re,sizeof(infore),1,doc);
				if(cod==re.codigo)
				{
					do
					{
						cout<<"\n\t\tIdentidad: ";
						cin>>identidad;
						fflush(stdin);
						strcpy(re.identidad, Validar_identidad(identidad));
						
						if(strlen(identidad) != 13)
							cout<<"\a\n\t\t¡Error!, ingrese el número de identidad de nuevo."<<endl;
					}
					while (strlen(identidad)!=13);
					
					cout<<"\n\t\tNombre: ";
					gets(re.nombre);
					strupr(re.nombre);
					strcpy(re.nombre, Validar_respuesta_texto(re.nombre));
					cout<<"\n\t\tApellido: ";
					gets(re.apellido);
					strupr(re.apellido);
					strcpy(re.apellido, Validar_respuesta_texto(re.apellido));
					cout<<"\n\t\tContraseña: ";
					gets(contrasena);
					strcpy(re.contrasena, Validar_contrasena(contrasena));
					fflush(stdin);
					int pos=ftell(doc)-sizeof(re); 
					fseek(doc,pos,SEEK_SET);
					fwrite(&re,sizeof(infore),1,doc);
					cout<<"\n\t\t";
					system("pause");
					break;
				}
			}
			fclose(doc);	
		}
		else
		{
			return;
		}	
	}
}

// Función para modificar alumnos.

void modificar_alumno()
{
	char resp, grado[30], identidad[14], contrasena[30], codigo[30];
	bool bandera=false;
	int c=1, ca, cod;
	
	system("cls");
	fflush(stdin);
	fflush(stdout);
	ca=c_alum(doc); 
	cout<<"\n\t\t\t--------------------------------------";
	cout<<"\n\t\t\t-          MODIFICAR ALUMNOS         -";
	cout<<"\n\t\t\t--------------------------------------";
	cout<<"\n\n\t\tCódigo del alumno a modificar: ";
	cin>>codigo;
	cod = Validar_num_entero(codigo, 1, 9999);
	fflush(stdin);
	doc=fopen("alumnos.dat","rb");
	fseek(doc,0,0);
	
	while((!(feof(doc))) && (c<=ca))
	{
		fread(&alum,sizeof(alum),1,doc);
		if(cod==alum.codigo_alumno)
		{
			cout<<"\n\t\tIdentidad: "<<alum.identidad<<"\n\t\tNombre: "<<alum.nombre<<"\n\t\tApellido: "<<alum.apellido<<"\n\t\tGrado: "<<alum.grado<<"\n\t\tContraseña: "<<alum.contrasena;
			bandera=true;
			c=ca;
		}
		c++;
	}
	fclose(doc);
	
	fflush(stdin);
	
	if(bandera==false)
	{
		cout<<"\a\n\t\t¡Alumno no encontrado!"<<endl;
		cout<<"\n\t\t";
		system("pause");
	}
	else
	{
		cout<<"\n\n\t\t¿Desea proceder a modificar este alumno? [S/N]: ";
		cin>>resp;
		resp=toupper(resp);
		resp=Validar_respuesta_repetir(resp);
		
		if (resp=='S')
		{
			fflush(stdin);
			doc=fopen("alumnos.dat","r+b");
			fseek(doc,0,0);
			while( (!(feof(doc))) )
			{
				fread(&alum,sizeof(alum),1,doc);
				if(cod==alum.codigo_alumno)
				{
					do
					{
						cout<<"\n\t\tIdentidad: ";
						cin>>identidad;
						fflush(stdin);
						strcpy(alum.identidad, Validar_identidad(identidad));
						
						if(strlen(identidad) != 13)
							cout<<"\a\n\t\t¡Error!, ingrese el número de identidad de nuevo."<<endl;
					}
					while (strlen(identidad)!=13);
					
					cout<<"\n\t\tNombre: ";
					gets(alum.nombre); 
					strupr(alum.nombre);
					strcpy(alum.nombre, Validar_respuesta_texto(alum.nombre));
					cout<<"\n\t\tApellido: ";
					gets(alum.apellido);
					strupr(alum.apellido);
					strcpy(alum.apellido, Validar_respuesta_texto(alum.apellido));
					cout<<"\n\t\tGrado: ";
					cin>>grado;
					alum.grado = Validar_num_entero(grado, 1, 6);
					fflush(stdin);
					cout<<"\n\t\tContraseña: ";
					gets(contrasena);
					strcpy(alum.contrasena, Validar_contrasena(contrasena));
					fflush(stdin);
					fflush(stdout);
					int pos=ftell(doc)-sizeof(alum); 
					fseek(doc,pos,SEEK_SET);
					fwrite(&alum,sizeof(infoalumnos),1,doc);
					cout<<"\n\t\t";
					system("pause");
					break;
				}
			}
			fclose(doc);
		}
		else
		{
			return;
		}
	}
}

// Función para modificar maestros.

void modificar_maestro()
{
	char resp, sueldo[30], contrasena[30], codigo[30], identidad[14];
	bool bandera=false;
	int c=1, ca, cod;
	
	system("cls");
	fflush(stdin);
	fflush(stdout);
	ca=c_mas(doc); 
	cout<<"\n\t\t\t--------------------------------------";
	cout<<"\n\t\t\t-         MODIFICAR MAESTROS         -";
	cout<<"\n\t\t\t--------------------------------------";
	cout<<"\n\n\t\tCódigo del maestro a modificar: ";
	cin>>codigo;
	cod = Validar_num_entero(codigo, 1, 9999);
	fflush(stdin);
	doc=fopen("maestros.dat","rb");
	fseek(doc,0,0);
	
	while((!(feof(doc))) && (c<=ca))
	{
		fread(&mas,sizeof(infomaestros),1,doc);
		if(cod==mas.codigo_maestro)
		{
			cout<<"\n\t\tIdentidad: "<<mas.identidad<<"\n\t\tNombre: "<<mas.nombre<<"\n\t\tApellido: "<<mas.apellido<<"\n\t\tContraseña: "<<mas.contrasena<<"\n\t\tProfesión: "<<mas.profesion<<"\n\t\tSueldo: "<<mas.sueldo;
			bandera=true;
			c=ca;
		}
		c++;
	}
	fclose(doc);
	
	fflush(stdin);
	
	if(bandera==false)
	{
		cout<<"\a\n\t\t¡Maestro no encontrado!"<<endl;
		cout<<"\n\t\t";
		system("pause");
	}
	else
	{
		cout<<"\n\n\t\t¿Desea proceder a modificar este maestro? [S/N]: ";
		cin>>resp;
		resp=toupper(resp);
		resp=Validar_respuesta_repetir(resp);
		
		if (resp=='S')
		{
			fflush(stdin);
			doc=fopen("maestros.dat","r+b");
			fseek(doc,0,0);
			while( (!(feof(doc))) )
			{
				fread(&mas,sizeof(infomaestros),1,doc);
				if(cod==mas.codigo_maestro)
				{
					do
					{
						cout<<"\n\t\tIdentidad: ";
						cin>>identidad;
						fflush(stdin);
						strcpy(mas.identidad, Validar_identidad(identidad));
						
						if(strlen(identidad) != 13)
							cout<<"\a\n\t\t¡Error!, ingrese el número de identidad de nuevo."<<endl;
					}
					while (strlen(identidad)!=13);
					
					cout<<"\n\t\tNombre: ";
					gets(mas.nombre);
					strupr(mas.nombre);
					strcpy(mas.nombre, Validar_respuesta_texto(mas.nombre));
					cout<<"\n\t\tApellido: ";
					gets(mas.apellido);
					strupr(mas.apellido);
					strcpy(mas.apellido, Validar_respuesta_texto(mas.apellido));
					cout<<"\n\t\tContraseña: ";
					gets(contrasena);
					strcpy(mas.contrasena, Validar_contrasena(contrasena));
					fflush(stdin);
					cout<<"\n\t\tProfesión: ";
					gets(mas.profesion);
					strupr(mas.profesion);
					fflush(stdin);
					cout<<"\n\t\tSueldo: ";
					cin>>sueldo;
					mas.sueldo = Validar_num_entero(sueldo, 8000, 25000);
					int pos=ftell(doc)-sizeof(mas); 
					fseek(doc,pos,SEEK_SET);
					fwrite(&mas,sizeof(infomaestros),1,doc);
					cout<<"\n\t\t";
					system("pause");
					break;
				}
			}
			fclose(doc);	
		}
		else
		{
			return;
		}	
	}
}

/************************************* FUNCIONES PARA LISTAR *******************************************************/

// Función para listar los administradores.

void listar_admin()
{
	int c=0, ca, i=0;
	system("cls");
	fflush(stdin);
	ca=c_reg(doc); 
	cout<<"\n\t\t\t--------------------------------------";
	cout<<"\n\t\t\t-           ADMINISTRADORES          -";
	cout<<"\n\t\t\t--------------------------------------";
	doc=fopen("registro.dat","rb");
	fseek(doc,0,0);
	while( (!(feof(doc))) && (c<ca) )
	{
		fread(&re,sizeof(infore),1,doc);
		cout<<"\n\n\t\tCódigo: "<<re.codigo<<"\n\t\tIdentidad: "<<re.identidad<<"\n\t\tNombre: "<<re.nombre<<"\n\t\tApellido: "<<re.apellido<<"\n\t\tContraseña: "<<re.contrasena;
		c++;
	}
	fclose(doc);
	cout<<"\n\n\t\t";
	system("pause");
}

// Función para listar los alumnos.

void listar_alumno()
{
	int c=0, ca, i=0;
	system("cls");
	fflush(stdin);
	ca=c_alum(doc); 
	cout<<"\n\t\t\t--------------------------------------";
	cout<<"\n\t\t\t-               ALUMNOS              -";
	cout<<"\n\t\t\t--------------------------------------";
	doc=fopen("alumnos.dat","rb");
	fseek(doc,0,0);
	while( (!(feof(doc))) && (c<ca) )
	{
		fread(&alum,sizeof(alum),1,doc);
		cout<<"\n\n\t\tCodigo: "<<alum.codigo_alumno<<"\n\t\tIdentidad: "<<alum.identidad<<"\n\t\tNombre: "<<alum.nombre<<"\n\t\tApellido: "<<alum.apellido<<"\n\t\tGrado: "<<alum.grado<<"\n\t\tContrasena: "<<alum.contrasena;
		c++;
	}
	fclose(doc);
	cout<<"\n\n\t";
	system("pause");
}

// Función para listar los maestros.

void listar_maestro()
{
	int c=0, ca, i=0;
	system("cls");
	fflush(stdin);
	ca=c_mas(doc); 
	cout<<"\n\t\t\t--------------------------------------";
	cout<<"\n\t\t\t-              MAESTROS              -";
	cout<<"\n\t\t\t--------------------------------------";
	doc=fopen("maestros.dat","rb");
	fseek(doc,0,0);
	while( (!(feof(doc))) && (c<ca) )
	{
		fread(&mas,sizeof(infomaestros),1,doc);
		cout<<"\n\n\t\tCódigo: "<<mas.codigo_maestro <<"\n\t\tIdentidad: "<<mas.identidad<<"\n\t\tNombre: "<<mas.nombre<<"\n\t\tApellido: "<<mas.apellido<<"\n\t\tCodigo clase a impartir: "<<mas.codigo_clase<<"\n\t\tContraseña: "<<mas.contrasena<<"\n\t\tProfesión: "<<mas.profesion<<"\n\t\tSueldo: "<<mas.sueldo;
		c++;
	}
	fclose(doc);
	cout<<"\n\n\t\t";
	system("pause");
}

// listar promedio

void listar_promedio(int grado)
{
	float promedio[40];
	char nombre[40][40];
	system("cls");
	cout<<"\n\t\t\t--------------------------------------";
	cout<<"\n\t\t\t-          LISTAR PROMEDIO           -";
	cout<<"\n\t\t\t--------------------------------------";
	cout<<"\n\t\tCodigo Clase: "<<codigo_clase;
	cout<<"\n\t\tGrado: "<<grado<<endl;
	ordenar_promedio(grado, nombre, promedio);
}

 // ordenamiento de promedio 
 
void ordenar_promedio(int grado, char nombre[40][40], float promedio[40])
{
	
	int c=0, i=0, ca, codigo_alumno[50], contar=0;
	
	for(i=0; i<MAX; i++)
	{
		strcpy(nombre[i], " ");
		promedio[i]=0;
	}
	
	i=0;
	ca=c_alum(doc);
	doc=fopen("alumnos.dat","rb");
	fseek(doc,0,0);
	while( (!(feof(doc))) && (c<ca) )
	{
		fread(&alum,sizeof(alum),1,doc);
		if(grado==alum.grado)
		{
			strcpy(nombre[i],alum.nombre);
			codigo_alumno[i]=alum.codigo_alumno;
			contar++;
			i++;
		}
		c++;
	}
	fclose(doc);
	
	c=0;
	ca=c_alum_clase(doc);
	doc=fopen("alumnos_clases.dat","rb");
	fseek(doc,0,0);
	while( (!(feof(doc))) && (c<ca) )
	{
		fread(&alum_clases,sizeof(info_alum_clases),1,doc);
		if ( (codigo_alumno[c]==alum_clases.codigo_alumno) && (codigo_clase==alum_clases.codigo_clase) )
		{
			promedio[c]=alum_clases.promedio;
			c++;
		}
	}
	fclose(doc);
	
	char nombtemp[MAX];
	float promediotemp;
	for( i=0; i<contar; i++){
		for(int j=0; j<contar-1; j++){
			if(promedio[i]>promedio[j]){
				promediotemp=promedio[j];
				strcpy(nombtemp,nombre[j]);
				
				promedio[j]=promedio[i];
				strcpy(nombre[j],nombre[i]);
				
				promedio[i]=promediotemp;
				strcpy(nombre[i],nombtemp);
			}
		}
	}
	
	for(int i=0; i<contar; i++)
	{
		cout<<"\n\n\t\t"<<nombre[i]<<"\t"<<promedio[i];
	}
	cout<<"\n\n\t\t";
	system("pause");
}

// Función para listar las clases.

void listar_clase()
{
	int c=0, ca, i=0;
	fflush(stdin);
	ca=c_clase(doc);
	cout<<"\n\t\t\t--------------------------------------";
	cout<<"\n\t\t\t-               CLASES               -";
	cout<<"\n\t\t\t--------------------------------------";
	doc=fopen("clases.dat","rb");
	fseek(doc,0,0);
	while( (!(feof(doc))) && (c<ca) )
	{
		fread(&clas,sizeof(infoclases),1,doc);
		cout<<"\n\n\t\tCódigo: "<<clas.codigo_clase<<"\n\t\tNombre: "<<clas.nombre;
		c++;
	}
	fclose(doc);
}

// Función para listar los alumnos por grado.

void listado_alumnos()
{
	int c, ca, i, codigo;
	system("cls");
	fflush(stdin);
	cout<<"\n\t\t\t--------------------------------------";
	cout<<"\n\t\t\t-         LISTADO DE ALUMNOS         -";
	cout<<"\n\t\t\t--------------------------------------";
	
	c=0;
	ca=c_alum(doc);
	cout<<"\n\n\n\t\tPRIMER GRADO";
	cout<<"\n\t\t------ -----";
	doc=fopen("alumnos.dat","rb");
	fseek(doc,0,0);
	while( (!(feof(doc))) && (c<ca) )
	{
		fread(&alum,sizeof(infoalumnos),1,doc);
		if(alum.grado==1)
		{
			cout<<"\n\n\t\tCódigo: "<<alum.codigo_alumno<<"\n\t\tIdentidad: "<<alum.identidad<<"\n\t\tNombre: "<<alum.nombre<<"\n\t\tApellido: "<<alum.apellido;
		}	
		c++;
	}
	fclose(doc);
	
	c=0;
	ca=c_alum(doc);
	cout<<"\n\n\n\t\tSEGUNDO GRADO";
	cout<<"\n\t\t------- -----";
	doc=fopen("alumnos.dat","rb");
	fseek(doc,0,0);
	while( (!(feof(doc))) && (c<ca) )
	{
		fread(&alum,sizeof(infoalumnos),1,doc);
		if(alum.grado==2)
		{
			cout<<"\n\n\t\tCódigo: "<<alum.codigo_alumno<<"\n\t\tIdentidad: "<<alum.identidad<<"\n\t\tNombre: "<<alum.nombre<<"\n\t\tApellido: "<<alum.apellido;
		}
		c++;
	}
	fclose(doc);
	
	c=0;
	ca=c_alum(doc);
	cout<<"\n\n\n\t\tTERCER GRADO";
	cout<<"\n\t\t------ -----";
	doc=fopen("alumnos.dat","rb");
	fseek(doc,0,0);
	while( (!(feof(doc))) && (c<ca) )
	{
		fread(&alum,sizeof(infoalumnos),1,doc);
		if(alum.grado==3)
		{
		
			cout<<"\n\n\t\tCódigo: "<<alum.codigo_alumno<<"\n\t\tIdentidad: "<<alum.identidad<<"\n\t\tNombre: "<<alum.nombre<<"\n\t\tApellido: "<<alum.apellido;
		}	
		c++;
	}
	fclose(doc);
	
	c=0;
	ca=c_alum(doc);
	cout<<"\n\n\n\t\tCUARTO GRADO";
	cout<<"\n\t\t------ -----";
	doc=fopen("alumnos.dat","rb");
	fseek(doc,0,0);
	while( (!(feof(doc))) && (c<ca) )
	{
		fread(&alum,sizeof(infoalumnos),1,doc);
		if(alum.grado==4)
		{
			cout<<"\n\n\t\tCódigo: "<<alum.codigo_alumno<<"\n\t\tIdentidad: "<<alum.identidad<<"\n\t\tNombre: "<<alum.nombre<<"\n\t\tApellido: "<<alum.apellido;	
		}
		c++;
	}
	fclose(doc);
	
	c=0;
	ca=c_alum(doc);
	cout<<"\n\n\n\t\tQUINTO GRADO";
	cout<<"\n\t\t------ -----";
	doc=fopen("alumnos.dat","rb");
	fseek(doc,0,0);
	while( (!(feof(doc))) && (c<ca) )
	{
		fread(&alum,sizeof(infoalumnos),1,doc);
		if(alum.grado==5)
		{
			cout<<"\n\n\t\tCódigo: "<<alum.codigo_alumno<<"\n\t\tIdentidad: "<<alum.identidad<<"\n\t\tNombre: "<<alum.nombre<<"\n\t\tApellido: "<<alum.apellido;
		}	
		c++;
	}
	fclose(doc);
	
	c=0;
	ca=c_alum(doc);
	cout<<"\n\n\n\t\tSEXTO GRADO";
	cout<<"\n\t\t----- -----";
	doc=fopen("alumnos.dat","rb");
	fseek(doc,0,0);
	while( (!(feof(doc))) && (c<ca) )
	{
		fread(&alum,sizeof(infoalumnos),1,doc);
		if(alum.grado==6)
		{
			cout<<"\n\n\t\tCódigo: "<<alum.codigo_alumno<<"\n\t\tIdentidad: "<<alum.identidad<<"\n\t\tNombre: "<<alum.nombre<<"\n\t\tApellido: "<<alum.apellido;
		}		
		c++;
	}
	fclose(doc);
	
	cout<<"\n\n\t\t";
	system("pause");
}

// Función para listar las notas de cada alumno.

void listado_notas(int cod_alum, int cod_clase)
{
	int c=0, ca;
	ca=c_alum_clase(notas);
	notas=fopen("alumnos_clases.dat","rb");
	fseek(doc,0,0);
	while( (!(feof(notas))) && (c<ca) )
	{
		fread(&alum_clases,sizeof(info_alum_clases),1,notas);
		if (cod_alum==alum_clases.codigo_alumno && cod_clase==alum_clases.codigo_clase)
			cout<<"\n\t\tNota 1: "<<alum_clases.n1<<"\n\t\tNota 2: "<<alum_clases.n2<<"\n\t\tNota 3: "<<alum_clases.n3<<"\n\t\tNota 4: "<<alum_clases.n4<<"\n\t\tPromedio: "<<alum_clases.promedio;
		c++;
	}
	fclose(notas);
	cout<<"\n\n\t\t";
	system ("pause");
}
	
/******************************************* VALIDACIONES *******************************************************/

// Función para verificar que el código del administrador no esté repetido.

int Verificar_codigo_reg(int codigo)
{
	bool encontrado;
	
	do
	{
		encontrado = false;
		doc = fopen("registro.dat","r+b");
		fseek(doc,0,0);
		
		while(!(feof(doc)))
		{
			fread(&re,sizeof(infore),1,doc);
			
			if(re.codigo==codigo)
	    		encontrado=true;
	    }
	    
		fclose(doc);
		
	    if (encontrado==true)
		{
			cout<<"\a\n\t\t¡Error!, el código del administrador ya existe \n\n\t\tIngrese uno diferente: ";
			cin>>codigo;
		}
	}
	while(encontrado==true);
	
	return codigo;
}

// Función para verificar que el código del alumno no esté repetido.

int Verificar_codigo_alum(int codigo)
{
	bool encontrado=false;
	
	do
	{
		fflush(stdin);
		encontrado = false;
		doc = fopen("alumnos.dat","r+b");
		fseek(doc,0,0);
		
		while(!(feof(doc)))
		{
			fread(&alum,sizeof(infoalumnos),1,doc);
			
			if(alum.codigo_alumno==codigo)
	    		encontrado=true;
	    }
	    
		fclose(doc);
		
	    if (encontrado==true)
		{
			cout<<"\a\n\t\t¡Error!, el código del alumno ya existe \n\n\t\tIngrese uno diferente: ";
			scanf ("%d", &codigo);
		}
	}
	while(encontrado==true);
	
	return codigo;
}

// Función para verificar que el código del maestro no esté repetido.

int Verificar_codigo_mas(int codigo)
{
	bool encontrado;
	
	do
	{
		encontrado = false;
		doc = fopen("maestros.dat","r+b");
		fseek(doc,0,0);
		
		while(!(feof(doc)))
		{
			fread(&mas,sizeof(infomaestros),1,doc);
			
			if(mas.codigo_maestro==codigo)
	    		encontrado=true;
	    }
	    
		fclose(doc);
		
	    if (encontrado==true)
		{
			cout<<"\a\n\t\t¡Error!, el código del maestro ya existe \n\n\t\tIngrese uno diferente: ";
			cin>>codigo;
		}
	}
	while(encontrado==true);
	
	return codigo;
}

// Función para verificar que la identidad del alumno no esté repetida.

char * Verificar_identidad(char identidad[])
{
	bool encontrado;
	
	do
	{
		encontrado = false;
		
		doc = fopen("registro.dat","r+b");
		fseek(doc,0,0);
		
		while(!(feof(doc)))
		{
			fread(&re,sizeof(infore),1,doc);
			
			if(strcmp(re.identidad, identidad)==0)
	    		encontrado=true;
	    }
		fclose(doc);
		
		doc = fopen("alumnos.dat","r+b");
		fseek(doc,0,0);
		
		while(!(feof(doc)))
		{
			fread(&alum,sizeof(infoalumnos),1,doc);
			
			if(strcmp(alum.identidad, identidad)==0)
	    		encontrado=true;
	    }
		fclose(doc);
		
		doc = fopen("maestros.dat","r+b");
		fseek(doc,0,0);
		
		while(!(feof(doc)))
		{
			fread(&mas,sizeof(infomaestros),1,doc);
			
			if(strcmp(mas.identidad, identidad)==0)
	    		encontrado=true;
	    }
		fclose(doc);
		
	    if (encontrado==true)
		{
			cout<<"\a\n\t\t¡Error!, este numero de identidad ya existe. \n\n\t\tIngrese una diferente: ";
			cin>>identidad;
			fflush(stdin);
			strcpy(identidad, Validar_identidad(identidad));
		}
	}
	while(encontrado==true);
	
	return identidad;
}

// Función para verificar que el código de la clase no esté repetida para docentes.

int Verificar_codigo_clase(char codigo[30])
{
	int codigo_clas;
	bool encontrado;
	
	do
	{
		do
		{
			encontrado=false;
			for(int i=0; i<strlen(codigo); i++)
			{
				if(isalpha(codigo[i]) != 0)
					encontrado = true;
			}
			
			if (encontrado==true)
			{
				cout<<"\a\n\t\t¡Error!, solo se permiten numeros en este campo. \n\n\t\tIngrese uno diferente: ";
				cin>>codigo;
				fflush(stdin);
			}
		}while(encontrado==true);
			
		codigo_clas = Validar_num_entero(codigo, 1, 7);
		
		encontrado = false;
		
		for(int i=0; i<7; i++){
			if(clase[i]==codigo_clas)
				encontrado=true;
		}
			
	    if (encontrado==true)
		{
			cout<<"\a\n\t\t¡Error!, el código de la clase ya existe \n\n\t\tIngrese uno diferente: ";
			cin>>codigo;
			fflush(stdin);
		}
	}
	while(encontrado==true);
	
	return codigo_clas;
}

// Función para validar numeros enteros.

int Validar_num_entero(char respuesta[], int li, int ls)
{
	int val;
	
	do
	{
		val=atoi(respuesta);
		
		if (val == 0 || val < li || val > ls)
		{
			cout<<"\a\n\t\t¡Error! Ingrese una respuesta válida: ";
			cin>>respuesta;
		}
	}
	while(val==0 || val<li || val>ls);
	
	return val;
}

// Función para validar letras S y N.
char Validar_respuesta_repetir(char resp)
{
	do
	{
		if (resp!='S'&&resp!='N'){
			cout<<"\a\n\t\t¡Error! respuesta incorrecta, por favor ingrese [S/N]: ";
			cin>>resp;
			resp=toupper(resp);
		}
	}while(resp!='S'&&resp!='N');
	return resp;
}

// Validacion de campos de texto

char *Validar_respuesta_texto(char respuesta[30])
{
	
	int Indice;
	bool Verificar;
	
	do
	{
		Verificar = false;
		
		for(Indice=0; Indice<strlen(respuesta); Indice++)
		{
			if(isalpha(respuesta[Indice]) == 0)
				Verificar = true;
		}
		
		if(Verificar == true)
		{
			cout << "\a\n\t\t¡Error!, solo se permiten letras en este campo. \n\n\t\tIngrese de nuevo: ";
			cin >> respuesta;
			strupr(respuesta);
			fflush(stdin);
		}
	}
	while(Verificar == true);
	
	return respuesta;
}

// Validación de opciones con letras en secuencia usando colas.

char Validar_respuesta_letra(char Respuesta, char Primer_letra, char Ultima_letra)
{
	queue<char> Letras;
	bool Comprobar=false;
	
	while(Comprobar == false)
	{
		for(int Indice=Primer_letra; Indice<=Ultima_letra; Indice++)
			Letras.push(Indice);
		
		while(!Letras.empty())
		{
			if(Respuesta == Letras.front())
				Comprobar = true;
			
			Letras.pop();
		}
		
		if(Comprobar == true)
			return Respuesta;
		
		cout << "\a\n\t\t¡Error!, ingrese una opción válida: ";
		cin >> Respuesta;
		Respuesta = toupper(Respuesta);
	}
}

// Función para verificar contraseña.

char * Validar_contrasena(char Contrasena[])
{
	bool Verificar_mayusucula=false, Verificar_numero=false;
	int Indice=0;
	
	while(strlen(Contrasena) < 8)
	{
		cout << "\a\n\t\t¡Error!, la contraseña debe contener por lo menos ocho caracteres. \n\t\tIngresela de nuevo: ";
		cin >> Contrasena;
		fflush(stdin);
		Validar_contrasena(Contrasena);
	}
	
	for(int Indice=0; Indice<strlen(Contrasena); Indice++)
	{
		if(isupper(Contrasena[Indice]) != 0)
			Verificar_mayusucula = true;
		
		if(isdigit(Contrasena[Indice]) != 0)
			Verificar_numero = true;
	}
	
	if(Verificar_mayusucula == false)
	{
		cout << "\a\n\t\t¡Error!, la contraseña debe contener por lo menos una letra mayúscula. \n\t\tIngresela de nuevo: ";
		cin >> Contrasena;
		fflush(stdin);
		Validar_contrasena(Contrasena);
	}
	
	if(Verificar_numero == false)
	{
		cout << "\a\n\t\t¡Error!, la contraseña debe contener por lo menos un número. \n\t\tIngresela de nuevo: ";
		cin >> Contrasena;
		fflush(stdin);
		Validar_contrasena(Contrasena);
	}
	
	return Contrasena;
}

// Función para validar que solo sean caracteres en la identidad.

char * Validar_identidad(char Identidad[])
{
	int Indice;
	bool Verificar;
	
	do
	{
		Verificar = false;
		
		for(Indice=0; Indice<strlen(Identidad); Indice++)
		{
			if(isalpha(Identidad[Indice]) != 0)
				Verificar = true;
		}
		
		if(Verificar == true)
		{
			cout << "\a\n\t\t¡Error!, solo se permiten números en este campo. \n\n\t\tIngrese de nuevo: ";
			cin >> Identidad;
			fflush(stdin);
		}
	}
	while(Verificar == true);
	
	return Identidad;
}
