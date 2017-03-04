function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6354\" class=\"headerLeftMenuInActive\"><a id=\"aID6354\" href=\"#\" OnMouseOver=\"link('_dir','config0',this)\" class=\"leftMenuLinkHeadInActive\">config</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID856\" class=\"leftMenuInActive\"><a id=\"aID856\" href=\"#\" OnMouseOver=\"link('_class','Config54809',this)\" class=\"leftMenuLinkInActive\">Config</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Functions</div>\n");
document.write("<div id=\"divID3416\" class=\"leftMenuInActive\"><a id=\"aID3416\" href=\"#\" OnMouseOver=\"link('_member','CONFIG_ASPECT_RATIO_GetRatio4136944867',this)\" class=\"leftMenuLinkInActive\" onmouseover=\"overLibLeftMenu();return overlib('CONFIG_ASPECT_RATIO_GetRatio');\" onmouseout=\"return nd();\">CONFIG_ASPECT_RATIO_GetRa.<img src=\"../../../../../../../common/menunametolong.gif\"border=0></a></div>\n");
document.write("<div id=\"divID3414\" class=\"leftMenuInActive\"><a id=\"aID3414\" href=\"#\" OnMouseOver=\"link('_member','CONFIG_ASPECT_RATIO_GetString2854707291',this)\" class=\"leftMenuLinkInActive\" onmouseover=\"overLibLeftMenu();return overlib('CONFIG_ASPECT_RATIO_GetString');\" onmouseout=\"return nd();\">CONFIG_ASPECT_RATIO_GetSt.<img src=\"../../../../../../../common/menunametolong.gif\"border=0></a></div>\n");
document.write("<div id=\"divID3415\" class=\"leftMenuInActive\"><a id=\"aID3415\" href=\"#\" OnMouseOver=\"link('_member','CONFIG_ASPECT_RATIO_GetValue2854707291',this)\" class=\"leftMenuLinkInActive\" onmouseover=\"overLibLeftMenu();return overlib('CONFIG_ASPECT_RATIO_GetValue');\" onmouseout=\"return nd();\">CONFIG_ASPECT_RATIO_GetVa.<img src=\"../../../../../../../common/menunametolong.gif\"border=0></a></div>\n");
document.write("<div id=\"divID3417\" class=\"leftMenuInActive\"><a id=\"aID3417\" href=\"#\" OnMouseOver=\"link('_member','CONFIG_QUALITY_GetString2715270059',this)\" class=\"leftMenuLinkInActive\">CONFIG_QUALITY_GetString</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6225\" class=\"leftMenuInActive\"><a id=\"aID6225\" href=\"#\" OnMouseOver=\"link('_member','CONFIG_ASPECT_RATIO827376375',this)\" class=\"leftMenuLinkInActive\">CONFIG_ASPECT_RATIO</a></div>\n");
document.write("<div id=\"divID6226\" class=\"leftMenuInActive\"><a id=\"aID6226\" href=\"#\" OnMouseOver=\"link('_member','CONFIG_MODE827376375',this)\" class=\"leftMenuLinkInActive\">CONFIG_MODE</a></div>\n");
document.write("<div id=\"divID6227\" class=\"leftMenuInActive\"><a id=\"aID6227\" href=\"#\" OnMouseOver=\"link('_member','CONFIG_QUALITY827376375',this)\" class=\"leftMenuLinkInActive\">CONFIG_QUALITY</a></div>\n");
document.write("<div id=\"divID6228\" class=\"leftMenuInActive\"><a id=\"aID6228\" href=\"#\" OnMouseOver=\"link('_member','CONFIG_STATE827376375',this)\" class=\"leftMenuLinkInActive\">CONFIG_STATE</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
