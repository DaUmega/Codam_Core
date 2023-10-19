import { Injectable } from '@nestjs/common';
import axios from 'axios';
import * as bcrypt from 'bcrypt';
import * as speakeasy from 'speakeasy';
import { UsersService } from '../users/users.service';

const intraId = process.env.INTRA_ID;
const intraSecret = process.env.INTRA_SECRET;
const siteIP = process.env.VUE_APP_SITE_IP;
const apiKey = process.env.VUE_APP_SECRET;

@Injectable()
export class AuthService {
  constructor(private readonly usersService: UsersService) {}

  async initiateAuthentication(): Promise<string> {
    const authURL = `https://api.intra.42.fr/oauth/authorize?client_id=${intraId}&redirect_uri=http%3A%2F%2F${siteIP}%3A3000%2F${apiKey}%2Fauth-callback%2F&response_type=code`;
    return authURL;
  }

  async fetchUserData(code: string): Promise<string | { error: string }> {
    if (code) {
      try {
        // Make the POST request to get the access token
        const response = await axios.post(
          'https://api.intra.42.fr/oauth/token',
          {
            grant_type: 'authorization_code',
            client_id: intraId,
            client_secret: intraSecret,
            code: code,
            redirect_uri: `http://${siteIP}:3000/${apiKey}/auth-callback/`,
          }
        );
        const accessToken = response.data.access_token;

        // Use the access token for further requests
        const userDataResponse = await axios.get('https://api.intra.42.fr/v2/me', {
          headers: {
            Authorization: `Bearer ${accessToken}`,
          },
        });
        const theGoldenUsername = userDataResponse.data.login;

        const user = await this.usersService.findByLogin(theGoldenUsername);
        if (!user) {
          const createUserDto = { login: theGoldenUsername };
          await this.usersService.createUser(createUserDto);
          return `http://${siteIP}/login?${apiKey}=${theGoldenUsername}`;
        }
        else if(user.twoFacAuth) {
          return `http://${siteIP}/fa?user=${theGoldenUsername}`;
        }
        
        return `http://${siteIP}/login?${apiKey}=${theGoldenUsername}`;

      } catch (error) {
        console.error('Error:', error);
        return { error: 'Authentication failed' };
      }
    } else {
      console.error('Parameter "code" not found.');
      return { error: 'Parameter "code" not found' };
    }
  }

  async generateAndStoreSecretKey(username: string): Promise<string> {
    const user = await this.usersService.findByLogin(username);
    if (!user)
      return null;
    // Generate a random secret key
    const bytes = speakeasy.generateSecret({ length: 20 });
    const secretKey = bytes.base32;
    
    // Update Database
    user.twoFactorSecret = secretKey;
    user.twoFacAuth = false;
    await this.usersService.updateUser(user.id, user);

    // Return the secretKey for QR code
    return secretKey;
  }

  async verifySecretKey(username: string, verificationCode: string): Promise<boolean> {
    try {
      const user = await this.usersService.findByLogin(username);
      if (!user) {
        return false;
      }

      const currentTime = Math.floor(Date.now() / 1000);
      const timeStep = 30;
      const totpCode = speakeasy.totp({
        secret: user.twoFactorSecret,
        encoding: 'base32',
        time: currentTime,
        step: timeStep,
        digits: 6,
      });
      if (totpCode === verificationCode) {
        user.twoFacAuth = true;
        await this.usersService.updateUser(user.id, user);
      }

      return totpCode === verificationCode;
    } catch (error) {
      console.error('Error verifying secret key:', error);
      return false;
    }
  }
}
