import { ValidationPipe } from '@nestjs/common';
import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';

const siteIP = process.env.VUE_APP_SITE_IP;

async function bootstrap() {
  const app = await NestFactory.create(AppModule);
  app.enableCors({
    origin: `*`
  });
  app.useGlobalPipes(new ValidationPipe());
  // app.useGlobalPipes(new ValidationPipe({
  //   //whitelist: filter out properties that should NOT be received by a method  handler. 没用的会自动被过滤。
  //   //any property NOT included in the whitelist is automatically stripped from the resulting object.
  //   whitelist: true,
  //   //stop a reques from being processed if any non-white listed properties are present. 并throw an error。
  //   forbidNonWhitelisted: true,
  //   //transform the objcet into what we are expecting.
  //   transform: true,
  // })
  // );
  await app.listen(3000);
}
bootstrap();
