import { Body, Controller, Delete, Get, Param, Res, Post, Query } from '@nestjs/common';
import { AuthService } from './auth.service';

const apiKey = process.env.VUE_APP_SECRET;

@Controller(`${apiKey}/auth-secret`)
export class AuthController {
  constructor(private readonly authService: AuthService) {}

  @Get()
  async initiateAuthentication(@Res() res: any) {
    const authURL = await this.authService.initiateAuthentication();
    res.redirect(authURL);
  }
}

@Controller(`${apiKey}/auth-callback`)
export class AuthCallbackController {
  constructor(private readonly authService: AuthService) {}

  @Get()
  async fetchUserData(@Query('code') code: string, @Res() res: any) {
    const redirectUrlOrError = await this.authService.fetchUserData(code);
    if (typeof redirectUrlOrError === 'string') {
      res.redirect(redirectUrlOrError);
    } else {
      return redirectUrlOrError;
    }
  }
}

@Controller(`${apiKey}/twofa`)
export class AuthTwoFAController {
  constructor(private readonly authService: AuthService) {}

  @Get()
  async generateAndStoreSecretKey(@Query('user') username: string ) {
    const secretKey = await this.authService.generateAndStoreSecretKey(username);
    return { secretKey };
  }

  @Post()
  async verifySecretKey(@Body() verificationData: { username: string; verificationCode: string }) {
    const { username, verificationCode } = verificationData;
    const status = await this.authService.verifySecretKey(username, verificationCode);
    return status;
  }
}
