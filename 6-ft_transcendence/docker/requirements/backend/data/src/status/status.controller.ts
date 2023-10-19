import { Controller, Get } from '@nestjs/common';
import { StatusService } from './status.service';

const apiKey = process.env.VUE_APP_SECRET;

@Controller(`${apiKey}/status`)
export class StatusController {
  constructor(
    private statusService: StatusService,
  ){}

  @Get('test')
  printConnections() {
    this.statusService.listConnections();
  }
}