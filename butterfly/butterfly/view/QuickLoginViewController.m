//
//  QuickLoginViewController.m
//  WtloginDemo
//
//  Created by gavinsu on 13-10-15.
//  Copyright (c) 2013年 gavinsu. All rights reserved.
//

#import "QuickLoginViewController.h"
#import "AppDelegate.h"
#import "AsyncImageView.h"

@interface QuickLoginViewController ()

@property (nonatomic, strong) NSMutableArray *dataSourceArray;
@property (nonatomic, strong) UITableView    *accTableView;

@end

@implementation QuickLoginViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    
    if (!_dataSourceArray) {
        _dataSourceArray = [[NSMutableArray alloc] init];
    }
    
    [self _tableViewInit];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)dataSourceArrayInit
{
    //读取剪贴板，初始化_dataSourceArray
    if (!_dataSourceArray) {
        _dataSourceArray = [[NSMutableArray alloc] init];
    } else {
        [_dataSourceArray removeAllObjects];
    }
    [_dataSourceArray addObjectsFromArray:[g_loginSdk readUserListFromPasteboard_v2]];
    
    if (_dataSourceArray.count == 0) {
        DLog(@"_dataSourceArray.count = 0");
    }
    DLog(@"tagql _dataSourceArray.count = %d", _dataSourceArray.count);
    
    //debug begin.
    for (WloginUserInfo *u in _dataSourceArray) {
        DLog(@"u: %@", u);
    }
    //debug end.
    
    [_accTableView reloadData];
}

#pragma mark - Private

- (void)_tableViewInit
{
    CGRect tableRect = CGRectMake(0, 0, [UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height);
    _accTableView = [[UITableView alloc] initWithFrame:tableRect style:UITableViewStylePlain];
    
    _accTableView.backgroundColor = [UIColor whiteColor];
    
    _accTableView.dataSource = self;
    _accTableView.delegate = self;
    
    [self.view addSubview:_accTableView];
}


#pragma mark - UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    long tag = 0;
#if 1
    WloginUserInfo *u = [_dataSourceArray objectAtIndex:indexPath.row];

    BOOL bQuickLogin = [g_loginSdk quickLoginStart_v2:_url userAccount:@"164561963" sourceApplication:_sourceApplication andDelegate:self tag:&tag];
    if (bQuickLogin != WLOGIN_V2_SECCESS) {
        DLog(@"quickLoginStart_v2 err!!!");
    }
#else
    BOOL bQuickLogin = [g_loginSdk quickLoginCancelled_v2:_url andDelegate:self tag:&tag];
    if (bQuickLogin != WLOGIN_V2_SECCESS) {
        DLog(@"quickLoginCancelled_v2 err!!!");
    }
#endif
    
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
}

#pragma mark - UITableViewDataSource

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [_dataSourceArray count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = nil;
    static NSString *cell_ID = @"acclist_cells";
    cell = [tableView dequeueReusableCellWithIdentifier:cell_ID];
    
    if (cell == nil) {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:cell_ID];
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        cell.backgroundColor=[UIColor whiteColor];
        cell.contentView.backgroundColor = [UIColor clearColor];
    }
    
    WloginUserInfo *u = [_dataSourceArray objectAtIndex:indexPath.row];
    
    //faceView
    AsyncImageView *faceView = [[AsyncImageView alloc] initWithFrame:CGRectMake(1, 1, 40, 40)];
    if (u.sFaceUrl.length > 0) {
        NSURL *faceURL = [NSURL URLWithString:u.sFaceUrl];
        faceView.imageURL = faceURL;
    } else {
        faceView.image = [UIImage imageNamed:@"qq.jpg"];
    }
    [cell.contentView addSubview:faceView];
    
    //nickLabel
    UILabel *nickLabel = [[UILabel alloc] initWithFrame:CGRectMake(faceView.frame.size.width + 1,
                                                                   0,
                                                                   MainScreenHeight - faceView.frame.size.width,
                                                                   faceView.frame.size.height)];
    nickLabel.backgroundColor = [UIColor clearColor];
    nickLabel.textColor = [UIColor grayColor];
    nickLabel.font = [UIFont systemFontOfSize:18];
    nickLabel.text = u.sNickName;
    [cell.contentView addSubview:nickLabel];
    
    return cell;
}

#pragma mark - WloginCallbackProtocol_v2

-(void)quickLoginEnd_v2:(WloginSdk_v2 *)sdk andUrl:(NSURL *)url tag:(long)tag
{
    [self performSelector:@selector(_openUrl:) withObject:url afterDelay:2.0f];
}

-(void)_openUrl:(NSURL *)url
{
    [[UIApplication sharedApplication] openURL:url];
}

@end
