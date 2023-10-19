import { Module } from '@nestjs/common';
import { AuthService } from './auth.service';
import { AuthCallbackController, AuthController, AuthTwoFAController } from './auth.controller';
import { UsersModule } from '../users/users.module';

@Module({
	imports: [UsersModule],
	controllers: [AuthController, AuthCallbackController, AuthTwoFAController], //API routes that we want this module to instantiate.
  	providers: [AuthService],
})
export class AuthModule {}
