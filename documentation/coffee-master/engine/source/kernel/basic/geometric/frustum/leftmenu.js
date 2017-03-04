function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6274\" class=\"headerLeftMenuInActive\"><a id=\"aID6274\" href=\"#\" OnMouseOver=\"link('_dir','frustum0',this)\" class=\"leftMenuLinkHeadInActive\">frustum</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID734\" class=\"leftMenuInActive\"><a id=\"aID734\" href=\"#\" OnMouseOver=\"link('_class','Frustum339014',this)\" class=\"leftMenuLinkInActive\">Frustum3</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6209\" class=\"leftMenuInActive\"><a id=\"aID6209\" href=\"#\" OnMouseOver=\"link('_member','FRUSTUM3_CORNER7578827',this)\" class=\"leftMenuLinkInActive\">FRUSTUM3_CORNER</a></div>\n");
document.write("<div id=\"divID6208\" class=\"leftMenuInActive\"><a id=\"aID6208\" href=\"#\" OnMouseOver=\"link('_member','FRUSTUM3_PLANE7578827',this)\" class=\"leftMenuLinkInActive\">FRUSTUM3_PLANE</a></div>\n");
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
