#define _GNU_SOURCE
#include <magick/api.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <math.h>
#include <unistd.h>

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

void		dump_histogram(int *histogram, char *path)
{
  int		fd = open(path, O_CREAT|O_TRUNC|O_RDWR, 0755);
  int		i = 0;
  char		*val;

  while (i < 255)
    {
      asprintf(&val, "%i\n", histogram[i]);
      write(fd, val, strlen(val));
      i++;
    }
  close(fd);
}

int		*create_histogram(Image *img)
{
  int		i = 0;
  int		*histogram = malloc(256 * sizeof(*histogram));
  PixelPacket	*px;
  int		size;

  px = GetImagePixels(img, 0, 0, img->columns, img->rows);
  //  memset(histogram, 0, 255);
  while (i < 255)
    histogram[i++] = 0;
  size = img->columns * img->rows;
  i = 0;
  while (i < size)
    {
       histogram[(int)px[i].blue] += 1;
      i++;
    }
  return (histogram);
}

// image[i] == 1 pixel_content

Image		*get_grayscale_image(Image *img)
{
  QuantizeInfo	info;

  GetQuantizeInfo(&info);
  info.colorspace = GRAYColorspace;
  info.number_colors = 256;
  QuantizeImage(&info, img);
  return (img);
}

int		main(int ac, char **av)
{
  Image		*img;
  int		*histogram;

  InitializeMagick("./");
  img = get_image_from_path(av[1]);
  img = get_grayscale_image(img);
  histogram = create_histogram(img);
  dump_histogram(histogram, av[2]);
  dump_image(img, "./", "gray", "jpeg");
  return (0);
}





