#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <wand/MagickWand.h>
#include <magick/MagickCore.h>
#include <magick/statistic.h>
/* include <magick/image.h> 
   #include <magick/methods.h> */
/* include "magick/pixel-accessor.h" */

/* determines if an image is grayscale or colored by examining all pixels.
   Verifies the case of RGB formatted images that are actually grayscale. */   
char *colorspace_lookup(int colorspace);

int main(int argc, char **argv) {
  /* Much of this initialization code is directly from
     https://imagemagick.org/script/magick-core.php */
  ExceptionInfo
    *exception;

  BlobInfo
    *blob_info;
  
  Image
    *image,
    *images,
    *resize_image;

  ImageInfo
    *image_info;

  ChannelStatistics
    *stat;

  MagickBooleanType
    status;

  MagickPixelPacket
    pixel;

  MagickWand
    *color_wand,
    *statistic_wand,
    *image_wand;

  PixelIterator
    *iterator;

  PixelWand
    **pixels;


  register ssize_t
    x;

  size_t
    width;

  ssize_t
    y;
  
  if(argc < 2) {
    fprintf(stderr,"I need one or more filenames to operate on.\n");
    exit(0);
  }

  /* apparently *argv is passed to get the current path? I think this fails
     on OpenBSD; I will need to check later... Just using the example code.  */
  /* the boolean is for  if we should use MagickCore's signal handlers. */

  
  

/* define SigmoidalContrast(x)                                          \
   (QuantumRange*(1.0/(1+exp(10.0*(0.5-QuantumScale*x)))-0.0066928509)*1.0092503) */
#define ThrowWandException(wand) \
{ \
  char \
    *description; \
 \
  ExceptionType \
    severity; \
 \
  description=MagickGetException(wand,&severity); \
  (void) fprintf(stderr,"%s %s %lu %s\n",GetMagickModule(),description); \
  description=(char *) MagickRelinquishMemory(description); \
  exit(-1); \
}



  if (argc < 2)
    {
      (void) fprintf(stdout,"Usage: %s [image] \n",argv[0]);
      exit(0);
    }
  MagickWandGenesis();
  int i=1;
  while(i<argc) {
  /*
    Read an image.
  */
  image_wand=NewMagickWand();
  status=MagickReadImage(image_wand,argv[i]);
  if (status == MagickFalse)
    ThrowWandException(image_wand);
  
  /* color checker */
  iterator=NewPixelIterator(image_wand);
  
  iterator=DestroyPixelIterator(iterator);
  image=GetImageFromMagickWand(image_wand);

  int colorspace=GetImageColorspaceType(image, exception);

/*  printf("type %s\n",colorspace_lookup(colorspace)); */
  image_wand=DestroyMagickWand(image_wand);

/* todo: should really just be using an enum like imagemagick does. */
  printf("%s\t",argv[i]);
  /* if it is any of the following, we are _probably_ safe to assume grayscale */
  switch(colorspace)
  { 
    case 2:  /* GRAY */
    case 3:  /* Transparent */
    case 17: /* Rec. 601 Luma */
    case 19: /* Rec. 709 Luma */
    case 35: /* Linear GRAY Colorspace */
      printf("Grayscale\n");
      break;
    default:
      printf("Color\n");
  }

/*  image_wand=DestroyMagickWand(image_wand); */
  i++;
  }
  MagickWandTerminus();
/*
  iterator=NewPixelIterator(image_wand);
  contrast_iterator=NewPixelIterator(contrast_wand);
  if ((iterator == (PixelIterator *) NULL) ||
      (contrast_iterator == (PixelIterator *) NULL))
    ThrowWandException(image_wand);
  for (y=0; y < (ssize_t) MagickGetImageHeight(image_wand); y++)
  {
    pixels=PixelGetNextIteratorRow(iterator,&width);
    contrast_pixels=PixelGetNextIteratorRow(contrast_iterator,&width);
    if ((pixels == (PixelWand **) NULL) ||
        (contrast_pixels == (PixelWand **) NULL))
      break;
    for (x=0; x < (ssize_t) width; x++)
    {
      PixelGetMagickColor(pixels[x],&pixel);
      pixel.red=SigmoidalContrast(pixel.red);
      pixel.green=SigmoidalContrast(pixel.green);
      pixel.blue=SigmoidalContrast(pixel.blue);
      pixel.index=SigmoidalContrast(pixel.index);
      PixelSetMagickColor(contrast_pixels[x],&pixel);
    }
    (void) PixelSyncIterator(contrast_iterator);
  }
  if (y < (ssize_t) MagickGetImageHeight(image_wand))
    ThrowWandException(image_wand);
  contrast_iterator=DestroyPixelIterator(contrast_iterator);
  iterator=DestroyPixelIterator(iterator);
  image_wand=DestroyMagickWand(image_wand);


  */



  
  /*
    Write the image then destroy it.
  */

  /*
  status=MagickWriteImages(contrast_wand,argv[2],MagickTrue);
  if (status == MagickFalse)
    ThrowWandException(image_wand);
  contrast_wand=DestroyMagickWand(contrast_wand);
  MagickWandTerminus(); */

  return(0);
}

/* brittle; depends on imagemagick not changing these numerical values. */
char *colorspace_lookup(int colorspace) {
    switch(colorspace) {
    case 0:
      return "UndefinedColorspace";
    case 1:
      return "RGBColorspace";
    case 2:
      return "GRAYColorspace";           /* greyscale (non-linear) image (faked 1 channel) */
    case 3:
      return "TransparentColorspace";
    case 4:
      return "OHTAColorspace";
    case 5:
      return "LabColorspace";
    case 6:
      return "XYZColorspace";
    case 7:
      return "YCbCrColorspace";
    case 8:
      return "YCCColorspace";
    case 9:
      return "YIQColorspace";
    case 10:
      return "YPbPrColorspace";
    case 11:
      return "YUVColorspace";
    case 12:
      return "CMYKColorspace";           /* negated linear RGB with black separated */
    case 13:
      return "sRGBColorspace";           /* Default: non-linear sRGB colorspace */
    case 14:
      return "HSBColorspace";
    case 15:
      return "HSLColorspace";
    case 16:
      return "HWBColorspace";
    case 17:
      return "Rec601LumaColorspace";
    case 18:
      return "Rec601YCbCrColorspace";
    case 19:
      return "Rec709LumaColorspace";
    case 20:
      return "Rec709YCbCrColorspace";
    case 21:
      return "LogColorspace";
    case 22:
      return "CMYColorspace";            /* negated linear RGB colorspace */
    case 23:
      return "LuvColorspace";
    case 24:
      return "HCLColorspace";
    case 25:
      return "LCHColorspace";            /* alias for LCHuv */
    case 26:
      return "LMSColorspace";
    case 27:
      return "LCHabColorspace";          /* Cylindrical (Polar) Lab */
    case 28:
      return "LCHuvColorspace";          /* Cylindrical (Polar) Luv */
    case 29:
      return "scRGBColorspace";
    case 30:
      return "HSIColorspace";
    case 31:
      return "HSVColorspace";            /* alias for HSB */
    case 32:
      return "HCLpColorspace";
    case 33:
      return "YDbDrColorspace";
    case 34:
      return "xyYColorspace";
    case 35:
      return "LinearGRAYColorspace";
    default:
      return "(Unknown to imagemagick)";
    }
}