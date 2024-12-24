#ifndef VALIDATION_H
#define VALIDATION_H

#ifndef MAX_LINES
#define MAX_LINES 1000//読み取る行数
#endif

typedef struct	s_texture
{
	char	*north_path;//北のテクスチャパス
	char	*south_path;//南のテクスチャパス
	char	*east_path;//東のテクスチャパス
	char	*west_path;//西のテクスチャパス
	int		floor_color[3];//床のテクスチャパス
	int		*ceiling_color[3];//天井のテクスチャパス
	char	initial_value;//スタートの向き
} t_texture;

// typedef	struct	s_player
// {

// } t_player;

typedef struct	s_element
{
	t_texture	texture;
	char		**map_inf;//mapの情報０１(N,S,E,W)
	int			map_height;

} t_element;


#endif