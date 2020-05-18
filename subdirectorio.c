#include <conio.h>
#include <dos.h>
#include <stdio.h>
# define VIDEO 0x10

struct disco{
	int StructSize;
	int Level;
	long SectorsPerCluster;
	long BytesPerSector;
	long AvailableClusters;
	long TotalClusters;
	long AvailablePhysSectors;
	long TotalPhysSectors;
	long AvailableAllocationUnits;
	long TotalAllocationUnits;
	char Rsvd[64];
} bufer;
long vol;
int tam=352;
char nombreUnidad[] = "C";
char nombreruta[]="discos $";
char err[]="no se realizo la accion$";
char nombrearchivo[]="trabajo4.txt$";
char nombrerutad[10];

int Volumen(void){
	bufer.Level=0;
	asm{
		mov di, OFFSET bufer
		mov cx,tam
		mov dx,OFFSET nombreUnidad
		mov ax,7303h
		int 21h	}

	vol = (bufer.SectorsPerCluster * 512 * bufer.TotalClusters) / 1024;
	return vol;}

void crearsub(void){

	asm{
		mov ah,39h
		mov dx,OFFSET nombreruta
		int 21h
		jc errord		}
		printf(" Subdirectorio creado");
		asm jmp salir
		errord:
		asm{
			mov ah, 09h
			mov dx, OFFSET err
			int 21h
		}
		salir:

}

void eliminarsub(void){
	asm{
		mov ah,3Ah
		mov dx,OFFSET nombreruta
		int 21h
		jc errord
	}
	printf("subdir borrado");
		asm jmp salir
		errord:
		asm{
			mov ah, 09h
			mov dx, OFFSET err
			int 21h
		}
		salir:
}

void directorioa(void){
	nombrerutad[10]='$';
	asm{
		mov ah,47h
		mov dl,0
		mov si,OFFSET nombrerutad
		int 21h
		jc mostrar_error
		mov ah, 09h
		mov dx, OFFSET nombrerutad
		int 21h
		jmp salir	}
	mostrar_error:
	asm{
	mov dx, OFFSET err
	mov ah, 09h
	int 21h	}
	salir:}

void crearAr(void){

	asm{
		mov ah, 3ch
		mov cx, 0
		mov dx, offset nombrearchivo
		int 21h
		jc mostrar_error
	}
	printf("Archivo creado\n");
		asm jmp salir

	mostrar_error:
	asm{
	lea dx, err
	mov ah, 09h
	int 21h
	}
	salir:
}

void eliminarAr(void){
	asm{
		mov ah, 41h
		mov dx, offset nombrearchivo
		int 21h
		jc mostrar_error
	}
	printf("Archivo borrado");
	asm	jmp salir

	mostrar_error:
	asm{
	lea dx, err
	mov ah, 09h
	int 21h
	}
	salir:
}

int main(void){
	int op;
	clrscr();

	while(op!=7)
    {
		
		printf("           MENU:  \n");
		printf("1) Crear subdirectorio \n");
		printf("2) Borrar subdirectorio \n");
		printf("3) Ruta actual \n");
		printf("4) Crear archivo \n");
		printf("5) Eliminar archivo \n");
		printf("6) Volumen del disco \n");
		printf("7) Salir \n");
	scanf("%d", &op);
	switch(op)
	{
			case 1: crearsub();
			printf("\n");break;
			case 2: eliminarsub();
			printf("\n"); break;
			 case 3:directorioa();
			 printf("\n");
			 break;
			case 4: crearAr();
			printf("\n");
			break;
			case 5: eliminarAr();
			printf("\n");
			break;
			case 6: printf("Volumen del disco %i\n", Volumen()); break;
			case 7: printf("al fin");
	}
    }
	getch();
	return 0;
	}
