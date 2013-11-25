#define _GNU_SOURCE
#include <magick/api.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <math.h>

int		check_extension(char *file_name, char *extension)
{
  int		len = strlen(file_name);
  int		i;
  int		k = 0;

  i =  len - strlen(extension);
  while (i < len)
    {
      if (file_name[i] != extension[k])
	return(0);
      i++;
      k++;
    }
  return (1);
}

int   		dump_image(Image *img, char *root_path, char *name, char *image_type)
{
  char		*final_path;
  ImageInfo	*image_info;
  ExceptionInfo	exception;

  GetExceptionInfo(&exception);
  if ((image_info = CloneImageInfo((ImageInfo *)NULL)) == NULL) {
    CatchException(&exception);
    DestroyImageInfo(image_info);
    return -1;
  }

  asprintf(&final_path, "%s/%s.%s", root_path, name, image_type);
  strcpy(img->filename, final_path);
  WriteImage(image_info, img);
  free(final_path);
  DestroyImageInfo(image_info);
  return (0);
}

Image		*get_image_from_path(char *path)
{
  ImageInfo	*image_info;
  Image		*img;
  ExceptionInfo	exception;

  GetExceptionInfo(&exception);
  if ((image_info = CloneImageInfo((ImageInfo *)NULL)) == NULL) {
    CatchException(&exception);
    DestroyImageInfo(image_info);
    return (NULL);
  }

  strcpy(image_info->filename, path);

  if ((img = ReadImage(image_info, &exception)) == NULL)
    {
      CatchException(&exception);
      DestroyImageInfo(image_info);
      return (NULL);
    }
  DestroyImageInfo(image_info);
  return (img);
}

Image		*crop_image_from_path(char *path, RectangleInfo *portion)
{
  ImageInfo	*image_info;
  Image		*img;
  Image		*tmp;
  ExceptionInfo	exception;

  GetExceptionInfo(&exception);
  if ((image_info = CloneImageInfo((ImageInfo *)NULL)) == NULL) {
    CatchException(&exception);
    DestroyImageInfo(image_info);
    return (NULL);
  }

  strcpy(image_info->filename, path);

  if ((img = ReadImage(image_info, &exception)) == NULL)
    {
      CatchException(&exception);
      DestroyImageInfo(image_info);
      return (NULL);
    }

  tmp = img;

  if ((img = CropImage(img, portion, &exception)) == NULL) {
    CatchException(&exception);
    DestroyImage(tmp);
    DestroyImageInfo(image_info);
    return (NULL);
  }

  DestroyImage(tmp);
  DestroyImageInfo(image_info);
  return (img);
}

/*
if ((img = ConstituteImage(width, height, "I", CharPixel, hyperslab,
			     &exception)) == NULL) {
    CatchException(&exception);
    DestroyImageInfo(image_info);
    fclose_check(a->file);
    return;
  }
*/

Image		*get_red_channe_image(Image *img)
{
  unsigned int	i = 0;
  unsigned int	j = 0;
  PixelPacket	*px_original;
  PixelPacket	*px_new;
  Image		*new_img;
  ExceptionInfo	exception;
  ImageInfo	*new_img_info;

  GetExceptionInfo(&exception);
  if ((new_img_info = CloneImageInfo((ImageInfo *)NULL)) == NULL) {
    CatchException(&exception);
    DestroyImageInfo(new_img_info);
    return (NULL);
  }

  new_img_info->colorspace = RGBColorspace;
  new_img = AllocateImage(new_img_info);
  new_img->rows = img->rows;
  new_img->columns = img->columns;

  if ((px_original = GetImagePixelsEx(img, 0, 0, img->columns, img->rows, &exception)) == NULL)
    {
      DestroyImage(new_img);
      CatchException(&exception);
      return (NULL);
    }

  if ((px_new = SetImagePixelsEx(new_img, 0, 0, new_img->columns, new_img->rows, &exception)) == NULL)
    {
      DestroyImage(new_img);
      CatchException(&exception);
      return (NULL);
    }

  while (i < img->rows)
    {
      j = 0;
      while (j < img->columns)
	{
	  px_new[(new_img->columns * i) + j].red = px_original[(img->columns * i) + j].red;
	  px_new[(new_img->columns * i) + j].blue = 0;
	  px_new[(new_img->columns * i) + j].green = 0;
	  j++;
	}
      i++;
    }
  SyncImagePixels(new_img);

  DestroyImageInfo(new_img_info);

  return (new_img);
}

Image		*get_green_channe_image(Image *img)
{
  unsigned int	i = 0;
  unsigned int	j = 0;
  PixelPacket	*px_original;
  PixelPacket	*px_new;
  Image		*new_img;
  ExceptionInfo	exception;
  ImageInfo	*new_img_info;

  GetExceptionInfo(&exception);
  if ((new_img_info = CloneImageInfo((ImageInfo *)NULL)) == NULL) {
    CatchException(&exception);
    DestroyImageInfo(new_img_info);
    return (NULL);
  }

  new_img_info->colorspace = RGBColorspace;
  new_img = AllocateImage(new_img_info);
  new_img->rows = img->rows;
  new_img->columns = img->columns;

  if ((px_original = GetImagePixelsEx(img, 0, 0, img->columns, img->rows, &exception)) == NULL)
    {
      DestroyImage(new_img);
      CatchException(&exception);
      return (NULL);
    }

  if ((px_new = SetImagePixelsEx(new_img, 0, 0, new_img->columns, new_img->rows, &exception)) == NULL)
    {
      DestroyImage(new_img);
      CatchException(&exception);
      return (NULL);
    }

  while (i < img->rows)
    {
      j = 0;
      while (j < img->columns)
	{
	  px_new[(new_img->columns * i) + j].red = 0;
	  px_new[(new_img->columns * i) + j].blue = 0;
	  px_new[(new_img->columns * i) + j].green = px_original[(img->columns * i) + j].green;
	  j++;
	}
      i++;
    }
  SyncImagePixels(new_img);

  DestroyImageInfo(new_img_info);

  return (new_img);
}

Image		*get_blue_channe_image(Image *img)
{
  unsigned int	i = 0;
  unsigned int	j = 0;
  PixelPacket	*px_original;
  PixelPacket	*px_new;
  Image		*new_img;
  ExceptionInfo	exception;
  ImageInfo	*new_img_info;

  GetExceptionInfo(&exception);
  if ((new_img_info = CloneImageInfo((ImageInfo *)NULL)) == NULL) {
    CatchException(&exception);
    DestroyImageInfo(new_img_info);
    return (NULL);
  }

  new_img_info->colorspace = RGBColorspace;
  new_img = AllocateImage(new_img_info);
  new_img->rows = img->rows;
  new_img->columns = img->columns;

  if ((px_original = GetImagePixelsEx(img, 0, 0, img->columns, img->rows, &exception)) == NULL)
    {
      DestroyImage(new_img);
      CatchException(&exception);
      return (NULL);
    }

  if ((px_new = SetImagePixelsEx(new_img, 0, 0, new_img->columns, new_img->rows, &exception)) == NULL)
    {
      DestroyImage(new_img);
      CatchException(&exception);
      return (NULL);
    }

  while (i < img->rows)
    {
      j = 0;
      while (j < img->columns)
	{
	  px_new[(new_img->columns * i) + j].red = 0;
	  px_new[(new_img->columns * i) + j].blue = px_original[(img->columns * i) + j].blue;
	  px_new[(new_img->columns * i) + j].green = 0;
	  j++;
	}
      i++;
    }
  SyncImagePixels(new_img);

  DestroyImageInfo(new_img_info);

  return (new_img);
}

Image		*substract_grayscale_to_original(Image *img, Image *gray_img, int min, int max)
{
  unsigned int	i = 0;
  unsigned int	j = 0;
  PixelPacket	*px_original;
  PixelPacket	*px_gray;
  PixelPacket	*px_new;
  Image		*new_img;
  ExceptionInfo	exception;
  ImageInfo	*new_img_info;

  GetExceptionInfo(&exception);
  if ((new_img_info = CloneImageInfo((ImageInfo *)NULL)) == NULL) {
    CatchException(&exception);
    DestroyImageInfo(new_img_info);
    return (NULL);
  }

  new_img_info->colorspace = RGBColorspace;
  new_img = AllocateImage(new_img_info);
  new_img->rows = img->rows;
  new_img->columns = img->columns;

  if ((px_original = GetImagePixelsEx(img, 0, 0, img->columns, img->rows, &exception)) == NULL)
    {
      DestroyImage(new_img);
      CatchException(&exception);
      return (NULL);
    }

  if ((px_gray = GetImagePixelsEx(gray_img, 0, 0, img->columns, img->rows, &exception)) == NULL)
    {
      DestroyImage(new_img);
      CatchException(&exception);
      return (NULL);
    }

  if ((px_new = SetImagePixelsEx(new_img, 0, 0, new_img->columns, new_img->rows, &exception)) == NULL)
    {
      DestroyImage(new_img);
      CatchException(&exception);
      return (NULL);
    }

  while (i < img->rows)
    {
      j = 0;
      while (j < img->columns)
	{
	 if(px_gray[(new_img->columns * i) + j].red > max || px_gray[(new_img->columns * i) + j].red < min)
	 {
	    px_new[(new_img->columns * i) + j].red = 0;
	    px_new[(new_img->columns * i) + j].blue = 0;
	    px_new[(new_img->columns * i) + j].green = 0;
	 }
	 else
	 {
	   px_new[(new_img->columns * i) + j].red = px_original[(new_img->columns * i) + j].red;
	   px_new[(new_img->columns * i) + j].blue = px_original[(new_img->columns * i) + j].blue;
	   px_new[(new_img->columns * i) + j].green = px_original[(new_img->columns * i) + j].green;
	 }
	  j++;
	}
      i++;
    }
  SyncImagePixels(new_img);

  DestroyImageInfo(new_img_info);

  return (new_img);
}

unsigned char	get_contrasted_value(unsigned char min, unsigned char max,
				     unsigned char dataset_min, unsigned char dataset_max, unsigned char initial_value)
{
  float	ratio;
  unsigned char	final_value;

  ratio = (float)((float)((float)max - (float)min) / (float)((float)dataset_max - (float)dataset_min));
  final_value = min + round(initial_value * ratio);
  return (final_value);
}

Image		*apply_green_contrast(Image *img, unsigned char min, unsigned char max)
{
unsigned int	i = 0;
  unsigned int	j = 0;
  PixelPacket	*px_original;
  PixelPacket	*px_new;
  Image		*new_img;
  ExceptionInfo	exception;
  ImageInfo	*new_img_info;
  unsigned char pixel_value;
  unsigned int	height = img->rows;
  unsigned int	width = img->columns;
  unsigned int	dataset_min = 255;
  unsigned int	dataset_max = 0;

  GetExceptionInfo(&exception);
  if ((new_img_info = CloneImageInfo((ImageInfo *)NULL)) == NULL) {
    CatchException(&exception);
    DestroyImageInfo(new_img_info);
    return (NULL);
  }

  new_img_info->colorspace = RGBColorspace;
  new_img = AllocateImage(new_img_info);
  new_img->rows = img->rows;
  new_img->columns = img->columns;

  if ((px_original = GetImagePixelsEx(img, 0, 0, img->columns, img->rows, &exception)) == NULL)
    {
      DestroyImage(new_img);
      CatchException(&exception);
      return (NULL);
    }

  if ((px_new = SetImagePixelsEx(new_img, 0, 0, new_img->columns, new_img->rows, &exception)) == NULL)
    {
      DestroyImage(new_img);
      CatchException(&exception);
      return (NULL);
    }

  while (i < height)
    {
      j = 0;
      while (j < width)
	{
	  pixel_value = px_original[(width * i) + j].green;
	  if (pixel_value < dataset_min)
	    dataset_min = pixel_value;
	  if (pixel_value > dataset_max)
	    dataset_max = pixel_value;
	  j++;
	}
      i++;
    }

  i = 0;

  while (i < height)
    {
      j = 0;
      while (j < width)
	{
	  pixel_value = px_original[(width * i) + j].green;
	  pixel_value = (pixel_value >= 255 ? 254 : pixel_value);

	  pixel_value = get_contrasted_value(min, max, dataset_min, dataset_max, pixel_value);

	  px_new[(width * i) + j].red = 0;
	  px_new[(width * i) + j].green = pixel_value;
	  px_new[(width * i) + j].blue = 0;
	  j++;
	}
      i++;
    }

  SyncImagePixels(new_img);

  DestroyImageInfo(new_img_info);
  return(new_img);
}

Image		*get_green_grayscale_image(Image *img)
{
  unsigned int	i = 0;
  unsigned int	j = 0;
  PixelPacket	*px_original;
  Image		*new_img;
  ExceptionInfo	exception;
  unsigned char *new_raw_image;

  GetExceptionInfo(&exception);

  if ((px_original = GetImagePixelsEx(img, 0, 0, img->columns, img->rows, &exception)) == NULL)
    {
      CatchException(&exception);
      return (NULL);
    }

  new_raw_image = malloc((img->rows * img->columns) * sizeof(*new_raw_image));

  while (i < img->rows)
    {
      j = 0;
      while (j < img->columns)
	{
	  new_raw_image[(img->columns * i) + j] = px_original[(img->columns * i) + j].green;
	  j++;
	}
      i++;
    }

  if ((new_img = ConstituteImage(img->columns, img->rows, "I", CharPixel, new_raw_image, &exception)) == NULL) {
    CatchException(&exception);
    return (NULL);
  }

  free(new_raw_image);
  return (new_img);
}

int		main(int ac, char **av)
{
  char		*image_path;
  char		*image_name;
  RectangleInfo *portion;
  struct dirent **names;
  int		nb;
  int		i = 0;
  int		j = 0;
  Image		*img;
  Image		*img_channel;
Image		*img_tmp;

  ac = ac;

  InitializeMagick("./");

  portion = malloc(sizeof(*portion));

  portion->width = 5538 - 3602;
  portion->height = 1523;
  portion->x = 3602;
  portion->y = 0;


  nb = scandir(av[1], &names, NULL, versionsort);
  while (i < nb)
    {
      if (check_extension(names[i]->d_name, ".jpeg"))
	{
	  printf("\rImage => %i", j);
	  fflush(stdout);
	  asprintf(&image_path, "%s/%s", av[1], names[i]->d_name);
	  if ((img = get_image_from_path(image_path)) == NULL)
	    printf("Failed to load the image from disk!\n");
	  /*	  asprintf(&image_name, "%i_rgb", j);
	  	  img = crop_image_from_path(image_path, portion);
		  dump_image(img, "/media/Data/histology/brain_2", image_name, "jpeg");
		  free(image_name); */

	  if ((img_channel = get_red_channe_image(img)) == NULL)
	    printf("Filed to extract the red channel from the image");
	  asprintf(&image_name, "%i_r", j);
	  dump_image(img_channel, "/media/Data/histology/brain_1_r", image_name, "jpeg");
	  DestroyImage(img_channel);
	  free(image_name);

	  if ((img_channel = get_green_channe_image(img)) == NULL)
	    printf("Filed to extract the green channel from the image");
	  asprintf(&image_name, "%i_g", j);
	  dump_image(img_channel, "/media/Data/histology/brain_1_g", image_name, "jpeg");
	  free(image_name);
	  DestroyImage(img_channel);

	  if ((img_channel = get_blue_channe_image(img)) == NULL)
	    printf("Filed to extract the blue channel from the image");
	  asprintf(&image_name, "%i_b", j);
	  dump_image(img_channel, "/media/Data/histology/brain_1_b", image_name, "jpeg");
	  free(image_name);
	  DestroyImage(img_channel);



	if ((img_tmp = apply_green_contrast(img, 0, 100)) == NULL)
	    printf("Filed to extract the - channel from the image");
	  asprintf(&image_name, "%i_gr", j);
	  dump_image(img_tmp, "/media/Data/histology/brain_1_gr", image_name, "jpeg");
	  free(image_name);

/*	  DestroyImage(img_channel); */

	if ((img_channel = get_green_grayscale_image(img_tmp)) == NULL)
	    printf("Filed to extract the - channel from the image");
	  asprintf(&image_name, "%i_g", j);
	  dump_image(img_channel, "/media/Data/histology/brain_1_gr", image_name, "jpeg");
	  free(image_name);
	 DestroyImage(img_tmp);

	img_tmp = img_channel;

	if ((img_channel = substract_grayscale_to_original(img, img_tmp, 20, 255)) == NULL)
	    printf("Filed to extract the - channel from the image");
	  asprintf(&image_name, "%i_final", j);
	  dump_image(img_channel, "/media/Data/histology/brain_1_gr", image_name, "jpeg");
	  free(image_name);
	  DestroyImage(img_channel);

	 DestroyImage(img_tmp);

	  DestroyImage(img);
	  free(image_path);
	  j++;
	}
      i++;
    }
  printf("\n");
  return (0);
}
