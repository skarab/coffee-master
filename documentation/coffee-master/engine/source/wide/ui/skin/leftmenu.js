function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6440\" class=\"headerLeftMenuInActive\"><a id=\"aID6440\" href=\"#\" OnMouseOver=\"link('_dir','skin0',this)\" class=\"leftMenuLinkHeadInActive\">skin</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6439\" class=\"leftMenuInActive\"><a id=\"aID6439\" href=\"#\" OnMouseOver=\"link('_dir','renderer/renderer0',this)\" class=\"leftMenuLinkInActive\">renderer</a></div>\n");
document.write("<div id=\"divID6441\" class=\"leftMenuInActive\"><a id=\"aID6441\" href=\"#\" OnMouseOver=\"link('_dir','widget/widget0',this)\" class=\"leftMenuLinkInActive\">widget</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID996\" class=\"leftMenuInActive\"><a id=\"aID996\" href=\"#\" OnMouseOver=\"link('_class','Skin49249',this)\" class=\"leftMenuLinkInActive\">Skin</a></div>\n");
document.write("<div id=\"divID997\" class=\"leftMenuInActive\"><a id=\"aID997\" href=\"#\" OnMouseOver=\"link('_class','SkinContext49249',this)\" class=\"leftMenuLinkInActive\">SkinContext</a></div>\n");
document.write("<div id=\"divID998\" class=\"leftMenuInActive\"><a id=\"aID998\" href=\"#\" OnMouseOver=\"link('_class','SkinTheme49249',this)\" class=\"leftMenuLinkInActive\">SkinTheme</a></div>\n");
document.write("<div id=\"divID999\" class=\"leftMenuInActive\"><a id=\"aID999\" href=\"#\" OnMouseOver=\"link('_class','SkinWidget49249',this)\" class=\"leftMenuLinkInActive\">SkinWidget</a></div>\n");
document.write("<div id=\"divID1000\" class=\"leftMenuInActive\"><a id=\"aID1000\" href=\"#\" OnMouseOver=\"link('_class','SkinWidgetState49249',this)\" class=\"leftMenuLinkInActive\">SkinWidgetState</a></div>\n");
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
