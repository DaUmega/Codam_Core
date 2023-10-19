import { Body, Controller, Get, Param, Post, Query } from '@nestjs/common';
import { CreateMatchDto } from './dto/create-match.dto';
import { MatchesService } from './matches.service';

const apiKey = process.env.VUE_APP_SECRET;

@Controller(`${apiKey}/matches`)
export class MatchesController {

	constructor(private readonly matchesService: MatchesService) {}

	@Get()
	findAll() {
		return this.matchesService.findAll();
	}

	@Get(':id')
	findUserAll(@Param('id') id: number) {
		return this.matchesService.findUserAll(id);
	}

	@Post()
	create(@Body() createMatchDto: CreateMatchDto) {
		return this.matchesService.createMatch(createMatchDto);
	}
}
