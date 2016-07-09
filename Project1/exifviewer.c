/*Project 1 EXIF Viewer
Reggie Barnett
rdb26@pitt.edu*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct exif{
	char manufact[20];
	char model[20];
	unsigned int Exp_speed[2];
	unsigned int F_stop[2];
	int ISO_speed;
	char date[20];
	unsigned int lens_length[2];
	int width;
	int height;	
};

struct tiff{
	unsigned short tag_id;
	unsigned short data_type;
	int num_data_types;
	int value;
};


int main(int argc, char *argv[])
{

	FILE *img_file;
	unsigned char filecheck[20];
	unsigned short tiff_tags[20];
	int i;
	int loc;
	/*done declaring variables*/

	img_file = fopen(argv[1], "rb");

	if(argc != 2)
		printf("Error: Inncorrect input\n");
	else{
			fread(filecheck,sizeof(char),20,img_file);
			/*verifying APP1 and file is II*/
			if(filecheck[3] != 0xE1 || filecheck[12] != 'I')
				printf("File doesn't work\n");
			/*Being check for TIFF tags*/
			else
			{
				struct exif exif_info;
				fread(tiff_tags,2,1,img_file);
				for(i=0;i<tiff_tags[0];i++)
				{
					struct tiff t;

					fread(&t,12,1,img_file);
					loc = ftell(img_file);

					if(t.tag_id == 0x010F) /*Manufacturer*/
					{
						fseek(img_file,t.value+12,SEEK_SET);
						fread(exif_info.manufact,2,t.num_data_types, img_file);
						printf("Manufacturer:\t%s\n",exif_info.manufact);
						fseek(img_file,loc,SEEK_SET);
					}
					if(t.tag_id == 0x0110) /*Model*/
					{
						fseek(img_file,t.value+12,SEEK_SET);
						fread(exif_info.model,2,t.num_data_types, img_file);
						printf("Model:\t\t%s\n",exif_info.model);
						fseek(img_file,loc,SEEK_SET);
					}
					if(t.tag_id == 0x8769)/*Exif sub bloack address*/
					{
						fseek(img_file,t.value+12,SEEK_SET);
						fread(tiff_tags,2,1,img_file);

						for(i=0;i<tiff_tags[0];i++)
						{
							fread(&t,12,1,img_file);
							loc = ftell(img_file);
							if(t.tag_id == 0xA002) /*Width*/
							{
								exif_info.width = t.value;
								printf("Width:\t\t%d pixels\n", exif_info.width);
								fseek(img_file,loc,SEEK_SET);
							}
							if(t.tag_id == 0xA003) /*Height*/
							{
								exif_info.height = t.value;
								printf("Height:\t\t%d pixels\n", exif_info.height);
								fseek(img_file,loc,SEEK_SET);
							}
							if(t.tag_id == 0x8827) /*ISO speed*/
							{
								exif_info.ISO_speed = t.value;
								printf("ISO:\t\tISO %d\n", exif_info.ISO_speed);
								fseek(img_file,loc,SEEK_SET);
							}
							if(t.tag_id == 0x829A) /*Exposure speed*/
							{
								fseek(img_file,t.value+12,SEEK_SET);
								fread(exif_info.Exp_speed,4,2,img_file);
								printf("Exposure Time:\t%d/%d second\n",exif_info.Exp_speed[0],exif_info.Exp_speed[1]);
								fseek(img_file,loc,SEEK_SET);
							}
							if(t.tag_id == 0x829D)/*F-stop*/
							{
								double FSTOP;
								fseek(img_file,t.value+12,SEEK_SET);
								fread(exif_info.F_stop,4,2,img_file);
								FSTOP = (double)exif_info.F_stop[0]/(double)exif_info.F_stop[1];
								printf("F-stop:\t\tf/%.1f\n",FSTOP);
								fseek(img_file,loc,SEEK_SET);
							}
							if(t.tag_id == 0x920A) /*Lens focal length*/
							{
								int FOCAL_LEN;
								fseek(img_file,t.value+12,SEEK_SET);
								fread(exif_info.lens_length,4,2,img_file);
								FOCAL_LEN = exif_info.lens_length[0]/exif_info.lens_length[1];
								printf("Focal Length:\t%d mm\n",FOCAL_LEN);
								fseek(img_file,loc,SEEK_SET);
							}
							if(t.tag_id == 0x9003) /*Date Taken*/
							{
								fseek(img_file,t.value+12,SEEK_SET);
								fread(exif_info.date,2,t.num_data_types,img_file);
								printf("Date Taken:\t%s\n",exif_info.date);
								fseek(img_file,loc,SEEK_SET);
							}
						}
					}
				}

			}
		}

	return 0;
}

