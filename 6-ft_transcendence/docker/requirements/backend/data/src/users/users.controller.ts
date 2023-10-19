import { Body, Controller, Delete, Get, Param, Patch, Post, Query, Res, UploadedFile, UseInterceptors } from '@nestjs/common';
import { FileInterceptor } from '@nestjs/platform-express';
import { CreateUserDto } from './dto/create-user.dto';
import { UpdateUserDto } from './dto/update-user.dto';
import { UsersService } from './users.service';
import { diskStorage } from 'multer';
import { extname } from 'path';

const apiKey = process.env.VUE_APP_SECRET;

@Controller(`${apiKey}/`) //detected from URL, for example: http://localhost:3000/users, then the reques will come to the 'users' controller.
export class UsersController {
	/*
	use constructors to inject a provider. Nest hadeles dependency injection.
	*/
	constructor(private readonly usersService: UsersService) {}

	/*
	if @Get('nickname'), the URL need to be: http://localhost:3000/users/nickname.
	*/
	// @Get()
	// findAll(@Query() paginationQuery) {
	// 	//const { limit, offset } = paginationQuery;
	// 	//return `This action returns all users. Limit: ${limit}, offset: ${offset}`;
	// 	return this.usersService.findAll();
	// }

	/*
	the @Param lets us grab all incoming request parameters and use them inside of the function body of method.
	如果是@Param()，则pass该object中的所有，引用某一项时需要params.id；如果只pass object中的id，则@Param('id'),引用时直接写id就行。
	*/
	@Get('loginid')
	findById(@Query('user') id: number) { //用了ValidationPipe中的transform, it automatically convert the String identifier fo a number.
		return this.usersService.findById(id);
	}

	// @Get(':login')
	// findByLogin(@Param('login') login: string) { //用了ValidationPipe中的transform, it automatically convert the String identifier fo a number.
	// 	return this.usersService.findByLogin(login);
	// }

	@Get('login') //login是通过@Param送进来的，还是通过@Body送进来的？
	async findByLogin(@Query('user') inComingLogin: string) { //用了ValidationPipe中的transform, it automatically convert the String identifier fo a number.
		return this.usersService.findByLogin(inComingLogin);
	}

	@Get('profilepic')
	async findProfilePic(@Query('user') inComingLogin: string, @Res() res: any) {
		const filePath = await this.usersService.findProfilePic(inComingLogin);
		return res.sendFile(filePath);
	}

	@Post('changename')
	async changeNickName(@Body() verificationData: { username: string; newNickName: string }) {
		const { username, newNickName } = verificationData;
		const status = await this.usersService.changeNickName(username, newNickName);
		return status;
	}

	@Post('profilepicchange')
	@UseInterceptors(
		FileInterceptor('profilePicture', {
			storage: diskStorage({
				destination: './uploads/',
				filename: (req, file, callback) => {
				const loginName = req.body.username;
				const fileExt = extname(file.originalname);
				return callback(null, `${loginName}${fileExt}`);
				},
			}),
			fileFilter: (req, file, callback) => {
				if (!file.originalname.match(/\.(jpg|jpeg|png)$/)) {
					return callback(new Error('Only JPG, JPEG, and PNG files are allowed!'), false);
				}
				callback(null, true);
			},
		}),
	)
	async changeProfilePic(@UploadedFile() file, @Body() verificationData: { username: string }) {
		const { username } = verificationData;
		if (!file || !username) {
			return false;
		}
	
		const status = await this.usersService.changeProfilePic(username, file.filename);
		return { status };
	}
	// @Post()
	// create(@Body() createUserDto: CreateUserDto) { //用了ValidationPipe中的transform, createUserDto就会是a instance of CreateUserDto
	// 	return this.usersService.createUser(createUserDto); 
	// }

	@Patch(':id')
	// update(@Param('id') id: number, @Body() updateUserDto: UpdateUserDto) {
	// 	return this.usersService.updateUser(id, updateUserDto);
	// }

	@Delete(':id')
	remove(@Param('id') id: number) {
		return this.usersService.removeUser(id);
	}

	@Get('updateUserActivity/:login/:status')
	async updateUserActivity(
		@Param('login') login: string,
  		@Param('status') status: number,
	) {
		const user = await this.usersService.findByLogin(login);
		if (user) {
			this.usersService.updateUserActivity(user.id, status);
		}
	}
}
