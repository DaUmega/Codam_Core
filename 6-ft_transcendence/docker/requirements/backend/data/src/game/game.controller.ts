import { Controller, Get, Param, } from "@nestjs/common";
import { ApiCookieAuth, ApiNotFoundResponse, ApiOkResponse, ApiOperation, ApiTags } from '@nestjs/swagger';

@Controller('game')
@ApiCookieAuth()
@ApiTags('game')
export class GameController {
    @Get('id/:id')
    @ApiOperation({ summary: 'Get game by id' })
    @ApiOkResponse({ description: 'Game found', type: Object })
    @ApiNotFoundResponse({ description: 'Game not found' })
    async getGameById(@Param('id') id: string): Promise<any> {
        console.log("TESTING Get ID in GameController")
    }

    @Get('all')
    @ApiOperation({ summary: 'Get all games' })
    @ApiOkResponse({ description: 'Games found', type: Object })
    async getGames(): Promise<any> {
        console.log("TESTING Get All in GameController")
    }
}
