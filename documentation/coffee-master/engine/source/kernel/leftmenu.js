function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6510\" class=\"headerLeftMenuInActive\"><a id=\"aID6510\" href=\"#\" OnMouseOver=\"link('_dir','kernel0',this)\" class=\"leftMenuLinkHeadInActive\">kernel</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6266\" class=\"leftMenuInActive\"><a id=\"aID6266\" href=\"#\" OnMouseOver=\"link('_dir','basic/basic0',this)\" class=\"leftMenuLinkInActive\">basic</a></div>\n");
document.write("<div id=\"divID6294\" class=\"leftMenuInActive\"><a id=\"aID6294\" href=\"#\" OnMouseOver=\"link('_dir','core/core0',this)\" class=\"leftMenuLinkInActive\">core</a></div>\n");
document.write("<div id=\"divID6306\" class=\"leftMenuInActive\"><a id=\"aID6306\" href=\"#\" OnMouseOver=\"link('_dir','meta/meta0',this)\" class=\"leftMenuLinkInActive\">meta</a></div>\n");
document.write("<div id=\"divID6323\" class=\"leftMenuInActive\"><a id=\"aID6323\" href=\"#\" OnMouseOver=\"link('_dir','resource/resource0',this)\" class=\"leftMenuLinkInActive\">resource</a></div>\n");
document.write("<div id=\"divID6328\" class=\"leftMenuInActive\"><a id=\"aID6328\" href=\"#\" OnMouseOver=\"link('_dir','shell/shell0',this)\" class=\"leftMenuLinkInActive\">shell</a></div>\n");
document.write("<div id=\"divID6337\" class=\"leftMenuInActive\"><a id=\"aID6337\" href=\"#\" OnMouseOver=\"link('_dir','storage/storage0',this)\" class=\"leftMenuLinkInActive\">storage</a></div>\n");
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
