import { IsBoolean, IsNumber, IsOptional, IsString } from 'class-validator'
/*
will be used as an expected input object shape for the UsersController's POST request.
will help us be able to do things like make sue the request payload has everything we require befor running further code.
*/
export class CreateUserDto {
	@IsString()
	readonly login: string;
	// @IsString()
	// readonly nickname: string;
	// @IsString()
	// readonly avatar: string;
	// @IsNumber()
	// readonly currentStatus: number;
	// @IsBoolean()
	// readonly twoFacAuth: boolean;
	// @IsNumber()
	// @IsOptional()
	// readonly friends: number[];
}