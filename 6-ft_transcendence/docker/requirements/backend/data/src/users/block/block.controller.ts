import { Body, Controller, Get, HttpException, HttpStatus, Param, ParseIntPipe, Post, Query } from '@nestjs/common';
import { User } from '../entities/user.entity';
import { UsersService } from '../users.service';
import { BlockDto } from './dto/blockedit.dto';
import { BlockService } from './block.service';

const apiKey = process.env.VUE_APP_SECRET;

@Controller(`${apiKey}/block`)
export class BlockController {
	constructor(
		private readonly blockService: BlockService,
		private readonly usersService: UsersService,
	) {}

	//http://localhost:3000/apikey/block/are-blocked?idOne=1&idTwo=2
	@Get('are-blocked')
	async areFriends(
		@Query('idOne', ParseIntPipe) idOne: number,
		@Query('idTwo', ParseIntPipe) idTwo: number,
	) {
		return await this.blockService.areBlocked(idOne, idTwo);
	}

	//http://localhost:3000/apikey/block/list?idOne=1
	@Get('list')
	async getBlocked(
		@Query('idOne', ParseIntPipe) idOne: number,
	) {
		return await this.blockService.getBlocked(idOne);
	}

	//http://localhost:3000/apikey/block/block
	@Post('block')
	async addBlock(@Body() blockDto: BlockDto) {
		// check if both users exist
		const user: User = await this.usersService.findById(blockDto.userId);
		const blocked: User = await this.usersService.findById(blockDto.blockId);
		if (!user || !blocked) {
			throw new HttpException(
				'User does not exist',
				HttpStatus.BAD_REQUEST,
			);
		}
		if (user.id === blocked.id) {
			throw new HttpException(
				'Cannot block yourself',
				HttpStatus.BAD_REQUEST,
			);
		}
		// check current friend status between two users
		const areBlocked = await this.blockService.areBlocked(blockDto.userId, blockDto.blockId,);
		
		if (!areBlocked) {
			await this.blockService.addBlock(user, blocked);
		} else {
			throw new HttpException(
				'User and requested user are already blocked.',
				HttpStatus.UNAUTHORIZED,
			);
		}
	}

	//http://localhost:3000/apikey/block/unblock
	@Post('unblock')
	async unBlock(@Body() blockDto: BlockDto) {
		// check if both users exist
		const user: User = await this.usersService.findById(blockDto.userId);
		const blocked: User = await this.usersService.findById(blockDto.blockId);
		if (!user || !blocked) {
			throw new HttpException(
				'User does not exist',
				HttpStatus.BAD_REQUEST,
			);
		}
		// check current friend status between two users
		const areBlocked = await this.blockService.areBlocked(blockDto.userId, blockDto.blockId,);
		
		if (areBlocked) {
			await this.blockService.unBlock(user, blocked);
		} else {
			throw new HttpException(
				'User and requested user are already blocked.',
				HttpStatus.UNAUTHORIZED,
			);
		}
	}
}
