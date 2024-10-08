#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "sha1.h"
#include "helper.h"

/* blk0() and blk() perform the initial expand. */
#define blk0(i) (block->l[i] = (_ROTL(block->l[i],24)&0xFF00FF00) | (_ROTL(block->l[i],8)&0x00FF00FF))
#define blk(i) (block->l[i&15] = _ROTL(block->l[(i+13)&15]^block->l[(i+8)&15]^block->l[(i+2)&15]^block->l[i&15],1))

/* (R0+R1), R2, R3, R4 are the different operations used in SHA1 */
#define R0(v,w,x,y,z,i) z+=((w&(x^y))^y)+blk0(i)+0x5A827999+_ROTL(v,5);w=_ROTL(w,30);
#define R1(v,w,x,y,z,i) z+=((w&(x^y))^y)+blk(i)+0x5A827999+_ROTL(v,5);w=_ROTL(w,30);
#define R2(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0x6ED9EBA1+_ROTL(v,5);w=_ROTL(w,30);
#define R3(v,w,x,y,z,i) z+=(((w|x)&y)|(w&x))+blk(i)+0x8F1BBCDC+_ROTL(v,5);w=_ROTL(w,30);
#define R4(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0xCA62C1D6+_ROTL(v,5);w=_ROTL(w,30);

/* Hash a single 512-bit block. */
void Sha1Transform(
  uint32_t state[5],
  const uint8_t buffer[64]
)
{
  uint32_t a, b, c, d, e;
  typedef union
  {
    uint8_t c[64];
    uint32_t l[16];
  } UINT64LONG16;	
  UINT64LONG16 block[1];

  memcpy(block, buffer, 64);

  /* Copy context->state[] to working vars */
  a = state[0];
  b = state[1];
  c = state[2];
  d = state[3];
  e = state[4];
  
  /* 4 rounds of 20 operations each. Loop unrolled. */
  R0(a, b, c, d, e, 0);
  R0(e, a, b, c, d, 1);
  R0(d, e, a, b, c, 2);
  R0(c, d, e, a, b, 3);
  R0(b, c, d, e, a, 4);
  R0(a, b, c, d, e, 5);
  R0(e, a, b, c, d, 6);
  R0(d, e, a, b, c, 7);
  R0(c, d, e, a, b, 8);
  R0(b, c, d, e, a, 9);
  R0(a, b, c, d, e, 10);
  R0(e, a, b, c, d, 11);
  R0(d, e, a, b, c, 12);
  R0(c, d, e, a, b, 13);
  R0(b, c, d, e, a, 14);
  R0(a, b, c, d, e, 15);
  R1(e, a, b, c, d, 16);
  R1(d, e, a, b, c, 17);
  R1(c, d, e, a, b, 18);
  R1(b, c, d, e, a, 19);
  R2(a, b, c, d, e, 20);
  R2(e, a, b, c, d, 21);
  R2(d, e, a, b, c, 22);
  R2(c, d, e, a, b, 23);
  R2(b, c, d, e, a, 24);
  R2(a, b, c, d, e, 25);
  R2(e, a, b, c, d, 26);
  R2(d, e, a, b, c, 27);
  R2(c, d, e, a, b, 28);
  R2(b, c, d, e, a, 29);
  R2(a, b, c, d, e, 30);
  R2(e, a, b, c, d, 31);
  R2(d, e, a, b, c, 32);
  R2(c, d, e, a, b, 33);
  R2(b, c, d, e, a, 34);
  R2(a, b, c, d, e, 35);
  R2(e, a, b, c, d, 36);
  R2(d, e, a, b, c, 37);
  R2(c, d, e, a, b, 38);
  R2(b, c, d, e, a, 39);
  R3(a, b, c, d, e, 40);
  R3(e, a, b, c, d, 41);
  R3(d, e, a, b, c, 42);
  R3(c, d, e, a, b, 43);
  R3(b, c, d, e, a, 44);
  R3(a, b, c, d, e, 45);
  R3(e, a, b, c, d, 46);
  R3(d, e, a, b, c, 47);
  R3(c, d, e, a, b, 48);
  R3(b, c, d, e, a, 49);
  R3(a, b, c, d, e, 50);
  R3(e, a, b, c, d, 51);
  R3(d, e, a, b, c, 52);
  R3(c, d, e, a, b, 53);
  R3(b, c, d, e, a, 54);
  R3(a, b, c, d, e, 55);
  R3(e, a, b, c, d, 56);
  R3(d, e, a, b, c, 57);
  R3(c, d, e, a, b, 58);
  R3(b, c, d, e, a, 59);
  R4(a, b, c, d, e, 60);
  R4(e, a, b, c, d, 61);
  R4(d, e, a, b, c, 62);
  R4(c, d, e, a, b, 63);
  R4(b, c, d, e, a, 64);
  R4(a, b, c, d, e, 65);
  R4(e, a, b, c, d, 66);
  R4(d, e, a, b, c, 67);
  R4(c, d, e, a, b, 68);
  R4(b, c, d, e, a, 69);
  R4(a, b, c, d, e, 70);
  R4(e, a, b, c, d, 71);
  R4(d, e, a, b, c, 72);
  R4(c, d, e, a, b, 73);
  R4(b, c, d, e, a, 74);
  R4(a, b, c, d, e, 75);
  R4(e, a, b, c, d, 76);
  R4(d, e, a, b, c, 77);
  R4(c, d, e, a, b, 78);
  R4(b, c, d, e, a, 79);
  
  /* Add the working vars back into context.state[] */
  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;
  state[4] += e;
  
  /* Wipe variables */
  a = b = c = d = e = 0;

  memset(block, '\0', sizeof(block));
}

/* Initialize new SHA1 context. */
void Sha1Init(
  SHA1_CONTEXT* context
)
{
  /* SHA1 initialization constants */
  context->state[0] = 0x67452301;
  context->state[1] = 0xEFCDAB89;
  context->state[2] = 0x98BADCFE;
  context->state[3] = 0x10325476;
  context->state[4] = 0xC3D2E1F0;
  context->count[0] = context->count[1] = 0;
}

/* Processes partial message to be composed with the digest. */
void Sha1Update(
  SHA1_CONTEXT* context,
  const uint8_t* data, 
  size_t len)
{
  size_t i, j;

  j = context->count[0];	
  if ((context->count[0] += len << 3) < j)
  {
    context->count[1]++;
  }
  
  context->count[1] += (len >> 29);
  j = (j >> 3) & 63;
  if ((j + len) > 63)
  {
    memcpy(&context->buffer[j], data, (i = 64 - j));
    Sha1Transform(context->state, context->buffer);
    for (; i + 63 < len; i += 64)
    {
      Sha1Transform(context->state, &data[i]);
    }
    j = 0;
  }
  else
  {
    i = 0;
  }

  memcpy(&context->buffer[j], &data[i], len - i);
}

/* Final function to be used. Add padding and return the message digest. */
void Sha1Final(
  uint8_t* digest,
  SHA1_CONTEXT* context)
{
  unsigned i;
  uint8_t finalcount[8];
  uint8_t c;
  
  uint8_t* fcp = &finalcount[8];

  for (i = 0; i < 2; i++)
  {
    size_t t = context->count[i];

    for (int j = 0; j < 4; t >>= 8, j++)
    {
      *--fcp = (uint8_t)t;
    }			
  }

  c = 0200;
  Sha1Update(context, &c, 1);
  
  while ((context->count[0] & 504) != 448)
  {
    c = 0000;
    Sha1Update(context, &c, 1);
  }	
  Sha1Update(context, finalcount, 8);
  
  for (i = 0; i < 20; i++)
  {
    digest[i] = (uint8_t)((context->state[i >> 2] >> ((3 - (i & 3)) << 3)) & 255);
  }
  /* Wipe variables */
  memset(context, 0, sizeof(SHA1_CONTEXT));
  memset(&finalcount, 0, sizeof(finalcount));
}

void Sha1(
  uint8_t* digest,
  const void* rData,
  size_t dataSz)
{
  SHA1_CONTEXT ctx;

  Sha1Init(&ctx);
  Sha1Update(&ctx, (const uint8_t*)rData, dataSz);
  Sha1Final((uint8_t*)digest, &ctx);
}

int Sha1Stream(
  uint8_t* digest,
  FILE* pFile,
  const size_t sz)
{
  SHA1_CONTEXT ctx;
  Sha1Init(&ctx);
  uint8_t buff[16U];

  const size_t lBlockSz = sz % 16U;
  const size_t t = sz / 16U;

  for (size_t i = 0; i < t; i++)
  {
    if (fread(buff, 16U, 1, pFile) != 1)
    {
      return 1;
    }

    Sha1Update(&ctx, buff, 16U);
  }

  if (lBlockSz)
  {
    if (fread(buff, lBlockSz, 1, pFile) != 1)
    {
      return 1;
    }

    Sha1Update(&ctx, buff, lBlockSz);
  }

  Sha1Final((uint8_t*)digest, &ctx);

  /* Wipe buffer */
  memset(buff, 0, sizeof(buff));
  return 0;
}

void Sha1Cat(
  uint8_t* digest, 
  const void* data1, 
  const void* data2, 
  size_t data1Sz, 
  size_t data2Sz)
{
  SHA1_CONTEXT ctx;

  Sha1Init(&ctx);
  Sha1Update(&ctx, (const uint8_t*)data1, data1Sz);
  Sha1Update(&ctx, (const uint8_t*)data2, data2Sz);
  Sha1Final((uint8_t*)digest, &ctx);
}

int Sha1StreamCat(
  uint8_t* digest,
  const void* data1,
  FILE* data2,
  size_t data1Sz,
  size_t data2Sz)
{
  SHA1_CONTEXT ctx;
  uint8_t buff[16];
  
  size_t lBlockSz = data2Sz % 16U;
  size_t t = data2Sz / 16U;

  Sha1Init(&ctx);
  Sha1Update(&ctx, (const uint8_t*)data1, data1Sz);

  for (size_t i = 0; i < t; i ++)
  {
    if (fread(buff, 16U, 1, data2) != 1)
    {
      return 1;
    }

    Sha1Update(&ctx, buff, 16U);
  }

  if (lBlockSz)
  {
    if (fread(buff, lBlockSz, 1, data2) != 1)
    {
      return 1;
    }

    Sha1Update(&ctx, buff, lBlockSz);
  }

  Sha1Final((uint8_t*)digest, &ctx);

  /* Wipe buffer */
  memset(buff, 0, sizeof(buff));
  return 0;
}